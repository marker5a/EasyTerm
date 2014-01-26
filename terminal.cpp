#include <QtWidgets> 
#include "terminal.h"
#include <QStringList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QButtonGroup>
#include <QSignalMapper>
#include <QMutex>
#include <QKeySequence>
#include <QShortcut>
#include "macro_editor.h"

void terminal_app::close_terminal_app()
{
	// if com port is created, clean house
	if( this->port )
	{
		this->port->flush();
		delete this->port;
	}
}

terminal_app::terminal_app(QApplication *parent)
{
    setupUi(this); 												// this sets up GUI
    
    // connect closing event of window to cleanup
    connect(parent,SIGNAL(lastWindowClosed()),this,SLOT(close_terminal_app()));
    
    // setup version number in title
    this->setWindowTitle(this->windowTitle() + QString(_VERSION_NUMBER));
    
    // initialize variables
	this->port = 0;	
	this->comPortConnected = 0;
	this->pending_receive_text_newline=false;    
									
	connect_widgets();											// connect widgets with callbacks
	
	group_radio_buttons();										// group the radio buttons together
		
	this->status_bar = new class status_bar(this->statusbar);	// create and instance of the status_bar class
	
	load_settings();											// load the settings
	
	populate_com_port();										// fill in the com port combo box
						
	this->editor = new macro_editor(this);						// create instance of macro gui
	
	update_macro_button_names();								// load in the macro names from the settings and set the button names		
	
	setup_keybindings();										// link F1-F12 buttons to macro buttons
	
	connect(this->clear_settings_button,SIGNAL( clicked() ),this,SLOT( clear_settings() ) );
}

void terminal_app::setup_keybindings(void)
{
	// create the keybinding shortcuts
	QShortcut *m1 = new QShortcut(QKeySequence("F1"),this);
	QShortcut *m2 = new QShortcut(QKeySequence("F2"),this);
	QShortcut *m3 = new QShortcut(QKeySequence("F3"),this);
	QShortcut *m4 = new QShortcut(QKeySequence("F4"),this);
	QShortcut *m5 = new QShortcut(QKeySequence("F5"),this);
	QShortcut *m6 = new QShortcut(QKeySequence("F6"),this);
	QShortcut *m7 = new QShortcut(QKeySequence("F7"),this);
	QShortcut *m8 = new QShortcut(QKeySequence("F8"),this);
	QShortcut *m9 = new QShortcut(QKeySequence("F9"),this);
	QShortcut *m10 = new QShortcut(QKeySequence("F10"),this);
	QShortcut *m11 = new QShortcut(QKeySequence("F11"),this);
	QShortcut *m12 = new QShortcut(QKeySequence("F12"),this);
	
	// create a signalmapper to consolidate some of the function calls
	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(m1 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m2 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m3 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m4 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m5 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m6 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m7 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m8 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m9 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m10,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m11,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m12,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	
	// map macro names to consolidate into one routine call
	signalMapper->setMapping(m1,  "macro_1_");
	signalMapper->setMapping(m2,  "macro_2_");
	signalMapper->setMapping(m3,  "macro_3_");
	signalMapper->setMapping(m4,  "macro_4_");
	signalMapper->setMapping(m5,  "macro_5_");
	signalMapper->setMapping(m6,  "macro_6_");
	signalMapper->setMapping(m7,  "macro_7_");
	signalMapper->setMapping(m8,  "macro_8_");
	signalMapper->setMapping(m9,  "macro_9_");
	signalMapper->setMapping(m10,"macro_10_");
	signalMapper->setMapping(m11,"macro_11_");
	signalMapper->setMapping(m12,"macro_12_");
	
	// one time connect of macro buttons
	connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(press_macro_button(QString))) ;
}

void terminal_app::load_settings()
{
	// load the settings
		// create the handle to the settings	
		this->settings = new QSettings("Hammy Circuits", "Terminal");
		
		// load up settings with default settings if configuration is not set
		if( !this->settings->allKeys().size() )
		{
			
			qDebug() << "Loading default settings";
			
			this->settings->setValue("baud_rate" , "9600");
			this->settings->setValue("data_bits" , "8");
			this->settings->setValue("stop_bits" , "1");
			this->settings->setValue("parity" , "none");
			this->settings->setValue("hex_ascii_rx" , "Hex");
			this->settings->setValue("hex_ascii_tx" , "Hex");
			
			// handle the dialog window defaults for macro editing
			this->settings->setValue("macro_1_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_2_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_3_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_4_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_5_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_6_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_7_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_8_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_9_hex_ascii"  , "Hex" );
			this->settings->setValue("macro_10_hex_ascii" , "Hex" );
			this->settings->setValue("macro_11_hex_ascii" , "Hex" );
			this->settings->setValue("macro_12_hex_ascii" , "Hex" );
						
			this->settings->sync();
		}
		// if config is set, load up everything
		else
		{
			
			qDebug() << "Loading saved settings";
			
			set_checked_radio(this->baud_rate_group,this->settings->value("baud_rate").toString());
			set_checked_radio(this->data_bits_group,this->settings->value("data_bits").toString());
			set_checked_radio(this->stop_bits_group,this->settings->value("stop_bits").toString());
			set_checked_radio(this->parity_group,this->settings->value("parity").toString());
			set_checked_radio(this->hex_ascii_rx,this->settings->value("hex_ascii_rx").toString());
			set_checked_radio(this->hex_ascii_tx,this->settings->value("hex_ascii_tx").toString());
			this->autoscroll_check->setChecked(this->settings->value("autoscroll").toBool());
		}
		
		return;
}

void terminal_app::group_radio_buttons(void)
{
	// baud rate group
	this->baud_rate_group = new QButtonGroup;
	this->baud_rate_group->addButton(this->baud_256000_radio);
	this->baud_rate_group->addButton(this->baud_9600_radio);
	this->baud_rate_group->addButton(this->baud_56000_radio);
	this->baud_rate_group->addButton(this->baud_4800_radio);
	this->baud_rate_group->addButton(this->baud_600_radio);
	this->baud_rate_group->addButton(this->baud_14400_radio);
	this->baud_rate_group->addButton(this->baud_57600_radio);
	this->baud_rate_group->addButton(this->baud_1200_radio);
	this->baud_rate_group->addButton(this->baud_19200_radio);
	this->baud_rate_group->addButton(this->baud_115200_radio);
	this->baud_rate_group->addButton(this->baud_2400_radio);
	this->baud_rate_group->addButton(this->baud_128000_radio);
	this->baud_rate_group->addButton(this->baud_38400_radio);    
	
	// data bits group
	this->data_bits_group = new QButtonGroup;
	this->data_bits_group->addButton(this->data_bits_5_radio);
	this->data_bits_group->addButton(this->data_bits_6_radio);
	this->data_bits_group->addButton(this->data_bits_7_radio);
	this->data_bits_group->addButton(this->data_bits_8_radio);
	
	// stop bits group
	this->stop_bits_group = new QButtonGroup;
	this->stop_bits_group->addButton(this->stop_bits_1_radio);
	this->stop_bits_group->addButton(this->stop_bits_1_1_2_radio);
	this->stop_bits_group->addButton(this->stop_bits_2_radio);
	
	// parity group
	this->parity_group = new QButtonGroup;
	this->parity_group->addButton(this->parity_none_radio);
	this->parity_group->addButton(this->parity_odd_radio);
	this->parity_group->addButton(this->parity_even_radio);
	this->parity_group->addButton(this->parity_mark_radio);
	this->parity_group->addButton(this->parity_space_radio);
	
	// rx hex/ascii group
	this->hex_ascii_rx = new QButtonGroup;
	this->hex_ascii_rx->addButton(this->hex_rx_radio);
	this->hex_ascii_rx->addButton(this->ascii_rx_radio);
	
	// tx hex/ascii group
	this->hex_ascii_tx = new QButtonGroup;
	this->hex_ascii_tx->addButton(this->hex_tx_radio);
	this->hex_ascii_tx->addButton(this->ascii_tx_radio);
	
	// connect radio buttons to updating settings
	connect(this->baud_rate_group	, SIGNAL(buttonClicked(int))	, 	this, SLOT(save_gui_settings()));	
	connect(this->data_bits_group   , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->stop_bits_group   , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->parity_group	    , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->hex_ascii_rx      , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->hex_ascii_tx		, SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->autoscroll_check 	, SIGNAL( stateChanged(int))	,	this, SLOT(save_gui_settings()));
	
}


void terminal_app::populate_com_port()
{		
	// clear the com port
	this->com_port_combo->clear();    
	
	// grab the list and fill them in
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();    
	
	for (int i = 0; i < ports.size(); i++)
	{
		this->com_port_combo->addItem( 
		#ifdef __unix__
			ports[i].systemLocation() );
		#else
			ports[i].portName() );
		#endif
    }
    
    // try and set the com port last used
    int com_port_index = this->com_port_combo->findText(this->settings->value("com_port").toString());
    
    // if the com port is found in the current menu, select it, otherwise ignore
    if( com_port_index != -1 )
		this->com_port_combo->setCurrentIndex(com_port_index);	
}


void terminal_app::rx_ascii_hex()
{	
	this->pending_receive_text_newline = true;

	return;
}

void terminal_app::open_macro_editor()
{
	this->setDisabled(1);
	this->editor->exec();
	update_macro_button_names();
	this->setDisabled(0);
}

void terminal_app::connect_widgets()
{
	// basic widget connections to specific actions
	connect(this->connect_button,SIGNAL( clicked() ),this,SLOT( connect_serial_port() ));		
	connect(this->rescan_button,SIGNAL( clicked() ),this,SLOT( populate_com_port() ));		
	connect(this->rx_clear_button,SIGNAL( clicked() ),this->receive_text,SLOT( clear() ));		
	connect(this->ascii_rx_radio,SIGNAL( clicked() ),this,SLOT( rx_ascii_hex() ));		
	connect(this->hex_rx_radio,SIGNAL( clicked() ),this,SLOT( rx_ascii_hex() ));		
	connect(this->tx_clear_button,SIGNAL( clicked() ),this->transmit_text,SLOT( clear() ));		
	connect(this->send_button,SIGNAL( clicked() ),this,SLOT( transmit() ));
	connect(this->set_macro_button,SIGNAL( clicked() ),this,SLOT( open_macro_editor() ) );
	connect(this->quit_button,SIGNAL( clicked() ),this,SLOT( close() ) );
	connect(this->transmit_field,SIGNAL( returnPressed() ),this,SLOT( transmit() ) );
	
	// connect all buttons to update config
	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(this->m1_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m2_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m3_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m4_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m5_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m6_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m7_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m8_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m9_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m10_button,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m11_button,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m12_button,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	
	// map macro names to consolidate into one routine call
	signalMapper->setMapping(this->m1_button, "macro_1_");
	signalMapper->setMapping(this->m2_button, "macro_2_");
	signalMapper->setMapping(this->m3_button, "macro_3_");
	signalMapper->setMapping(this->m4_button, "macro_4_");
	signalMapper->setMapping(this->m5_button, "macro_5_");
	signalMapper->setMapping(this->m6_button, "macro_6_");
	signalMapper->setMapping(this->m7_button, "macro_7_");
	signalMapper->setMapping(this->m8_button, "macro_8_");
	signalMapper->setMapping(this->m9_button, "macro_9_");
	signalMapper->setMapping(this->m10_button,"macro_10_");
	signalMapper->setMapping(this->m11_button,"macro_11_");
	signalMapper->setMapping(this->m12_button,"macro_12_");
	
	// one time connect of macro buttons
	connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(press_macro_button(QString))) ;

}
void terminal_app::clear_settings()
{
	this->settings->clear();
}

void terminal_app::connect_serial_port()
{			
	// check if we are already connected to the com port
	if( !this->comPortConnected )
	{	
		QString comPort = this->com_port_combo->currentText();
		
		// create com port if it doesnt exist
		if( !this->port )
			this->port = new QSerialPort(comPort);
		
		this->comPortName = comPort.toStdString();		
		
		// check for error message
		qDebug() << this->port->open(QIODevice::ReadWrite);
		
		// configure the port
		this->port->setPortName(this->comPortName.c_str());
		this->port->setBaudRate(get_checked_radio(this->baud_rate_group).toInt());
		this->port->setFlowControl(QSerialPort::NoFlowControl);
		
		// get the acutal enum for parity
			enum QSerialPort::Parity parity;
			if( get_checked_radio(this->parity_group) == "none" )
				parity = QSerialPort::NoParity;
			if( get_checked_radio(this->parity_group) == "odd" )
				parity = QSerialPort::OddParity;
			if( get_checked_radio(this->parity_group) == "even" )
				parity = QSerialPort::EvenParity;		
			#if defined(Q_OS_WIN) || defined(qdoc)
			if( get_checked_radio(this->parity_group) == "mark" )
				parity = QSerialPort::MarkParity;
			#endif
			if( get_checked_radio(this->parity_group) == "space" )
				parity = QSerialPort::SpaceParity;
			this->port->setParity(parity);
		
		this->port->setDataBits((QSerialPort::DataBits)get_checked_radio(this->data_bits_group).toInt());
		
		// get the acutal stop bits
			enum QSerialPort::StopBits stop_bits;
			if( get_checked_radio(this->stop_bits_group) == "1" )
				stop_bits = QSerialPort::OneStop;
			if( get_checked_radio(this->stop_bits_group) == "2" )
				stop_bits = QSerialPort::TwoStop;
			#if defined(Q_OS_WIN) || defined(qdoc)
			if( get_checked_radio(this->stop_bits_group) == "1.5" )
				stop_bits = QSerialPort::OneAndHalfStop;
			#endif
			this->port->setStopBits(stop_bits);

		this->port->flush();
		
		// connect receiver on serial port to on_ready_read
		connect(this->port, SIGNAL(readyRead()), this, SLOT(rx_data_available()));
		

		
		if (!this->port->isOpen())
		{
			qDebug("Error connecting to com port");
			
			this->status_bar->update_status_bar_error_status("COM Port Error! " + this->port->errorString());
			
			this->comPortConnected = 0;
			this->send_button->setDisabled(true);
		}
		else
		{
			qDebug("COM port connected");
			this->status_bar->update_status_bar_connection_status("Connected to " + comPort );
			
			// save the gui settings
			save_gui_settings();
			
			// if a warning is present, show it
			if( this->port->errorString() != "No Error has occurred"  )
				this->status_bar->update_status_bar_error_status("WARNING: " + this->port->errorString());
							
			this->comPortConnected = 1;
			this->send_button->setEnabled(true);
		}		
	}
	// if we are disonnecting
	else
	{
		this->port->flush();
		delete this->port;
		this->port = 0;
		this->comPortConnected = 0;
		this->send_button->setDisabled(true);
		qDebug("COM port disconnected");
		this->status_bar->update_status_bar_connection_status("Disconnected");
		this->status_bar->clear_status_bar_error_status();
	}
	
	// disable the com port fields if we are connected or enable if disconnected
	toggle_com_port_fields(this->comPortConnected);
		
	//change title of connect field
	this->connect_button->setText(this->comPortConnected?"Disconnect":"Connect");
}

void terminal_app::write_to_port(QByteArray array)
{
	// only allow sending when com port is connected
	if( this->comPortConnected )
	{
		this->port->write(array.data() , array.size() );

	}
}

void terminal_app::transmit()
{
	
	QByteArray tx_array;
	int hex_error=1;	
		
	// dont even try and do anything unless the com port is connected
	if( !this->comPortConnected )
		return;	
		
	// translate text field if based on decision to do ascii or hex
	if( get_checked_radio(this->hex_ascii_tx) == "Hex" )
	{
		hex_error = this->hex_qstring_to_hex_array(this->transmit_field->text(),&tx_array);
		
		if( hex_error )
		{
			this->transmit_text->insertPlainText(array_to_hex_array(tx_array));
			this->transmit_text->insertPlainText("\n");
			
			// autoscroll tx field
			QTextCursor c =  this->transmit_text->textCursor();
			c.movePosition(QTextCursor::End);
			this->transmit_text->setTextCursor(c);
			
		}
	}
	else
	{
		tx_array = this->transmit_field->text().toLatin1();
		this->transmit_text->insertPlainText(tx_array);
		this->transmit_text->insertPlainText("\n");
		
		// autoscroll tx field
		QTextCursor c =  this->transmit_text->textCursor();
		c.movePosition(QTextCursor::End);
		this->transmit_text->setTextCursor(c);
		
	}
	
	if( !hex_error )
	{
		this->status_bar->update_status_bar_error_status("Invalid Hex String");
		return;
	}	
	this->write_to_port(tx_array);
	this->status_bar->clear_status_bar_error_status();	
	
}

void terminal_app::set_checked_radio(QButtonGroup *group,QString name)
{
	QList<QAbstractButton *> buttonList = group->buttons();
	for( int i = 0 ; i < buttonList.size(); i++ )
	{
		if( buttonList[i]->text() == name )
		{
			buttonList[i]->setChecked(true);
			return;
		}
	}
}

QString terminal_app::get_checked_radio(QButtonGroup *group)
{
	return group->checkedButton()->text();
}

void terminal_app::rx_data_available(void)
{	
	QByteArray bytes;
    int a = this->port->bytesAvailable();
    bytes.resize(a);
    this->port->read(bytes.data(), bytes.size());
    
    // if request for newline in receive field, try and process it
    if( this->pending_receive_text_newline )    
    {
		// clear the flag
		this->pending_receive_text_newline = false;
		
		// only insert the newline if content currently exists in the receive field
		if( this->receive_text->toPlainText().size() > 0 )
			this->receive_text->insertPlainText("\n");
	}
		
    
    // interpret incoming data as hex or ascii
	if( this->get_checked_radio(this->hex_ascii_rx) == "ASCII" )
		this->receive_text->insertPlainText(bytes);
	else
		this->receive_text->insertPlainText(array_to_hex_array(bytes));
	
	// autoscroll receive field if checked
	if( this->autoscroll_check->isChecked() )
	{
		QTextCursor c =  this->receive_text->textCursor();
		c.movePosition(QTextCursor::End);
		this->receive_text->setTextCursor(c);
	}
}

void terminal_app::toggle_com_port_fields(bool disable)
{
	// toggle fields
	this->rescan_button->setDisabled(disable);
	this->com_port_combo->setDisabled(disable);
	this->baud_256000_radio->setDisabled(disable);
	this->baud_9600_radio->setDisabled(disable);
	this->baud_56000_radio->setDisabled(disable);
	this->baud_4800_radio->setDisabled(disable);
	this->baud_600_radio->setDisabled(disable);
	this->baud_14400_radio->setDisabled(disable);
	this->baud_57600_radio->setDisabled(disable);
	this->baud_1200_radio->setDisabled(disable);
	this->baud_19200_radio->setDisabled(disable);
	this->baud_115200_radio->setDisabled(disable);
	this->baud_2400_radio->setDisabled(disable);
	this->baud_128000_radio->setDisabled(disable);
	this->baud_38400_radio->setDisabled(disable);    
	this->data_bits_5_radio->setDisabled(disable);
	this->data_bits_6_radio->setDisabled(disable);
	this->data_bits_7_radio->setDisabled(disable);
	this->data_bits_8_radio->setDisabled(disable);
	this->stop_bits_1_radio->setDisabled(disable);
	this->stop_bits_1_1_2_radio->setDisabled(disable);
	this->stop_bits_2_radio->setDisabled(disable);
	this->parity_none_radio->setDisabled(disable);
	this->parity_odd_radio->setDisabled(disable);
	this->parity_even_radio->setDisabled(disable);
	this->parity_mark_radio->setDisabled(disable);
	this->parity_space_radio->setDisabled(disable);
}

void terminal_app::press_macro_button(QString macro_name)
{
	
	QByteArray tx_array;
	int hex_error=1;
	
	// dont even try and do anything unless the com port is connected
	if( !this->comPortConnected )
		return;
	
	// get the content of the macro and store it in a string
	QString tx_string = this->settings->value(macro_name + "content").toString();
	
	// if macro is empty, ignore and display warning
	if( !tx_string.size() )
	{
		// show warning message
		this->status_bar->update_status_bar_error_status("WARNING: Macro '" + this->settings->value(macro_name + "name").toString() + "' is empty");
		
		// just quit
		return;
	}	
	
	// determine action based on hex or ascii
		// hex
		if( this->settings->value(macro_name + "hex_ascii") == "Hex" )
		{
			// convert the string into a byte array as hex
			hex_error = this->hex_qstring_to_hex_array(tx_string,&tx_array);
			
			// if the hex converted properly, show the hex in the tx field
			if( hex_error )
			{
				this->transmit_text->insertPlainText(array_to_hex_array(tx_array));
				this->transmit_text->insertPlainText("\n");
				
							
				// autoscroll tx field
				QTextCursor c =  this->transmit_text->textCursor();
				c.movePosition(QTextCursor::End);
				this->transmit_text->setTextCursor(c);
			}
		}
		// ascii
		else
		{
			// just get byte array and send it out
			tx_array = tx_string.toLatin1();
			this->transmit_text->insertPlainText(tx_array);
			this->transmit_text->insertPlainText("\n");
			
			// autoscroll tx field
			QTextCursor c =  this->transmit_text->textCursor();
			c.movePosition(QTextCursor::End);
			this->transmit_text->setTextCursor(c);
		}
	
	// if there was an error with parsing the hex string, display it and quit
	if( !hex_error )
	{
		this->status_bar->update_status_bar_error_status("Invalid Hex String for Macro \"" + this->settings->value(macro_name + "name").toString() +"\"");
		return;
	}
	
	// write it out on the serial port and clear the error
	this->write_to_port(tx_array);
	this->status_bar->clear_status_bar_error_status();
		
}

QByteArray terminal_app::array_to_hex_array(QByteArray array_in)
{
	
	QByteArray out;
	
	for( int i = 0; i < array_in.size(); i++ )
	{
		char string[3]="";
		sprintf( string, "%.2X", (unsigned char)((char)array_in[i]) );
		out.append(string);
		out.append(" ");
	}
	
	return out;
}

int terminal_app::hex_qstring_to_hex_array(QString hex_qstring,QByteArray *result)
{
	// if the string does not contain an even number of characters, return failure
	if( hex_qstring.size()%2 != 0 )
		return 0;
		
	// iterate through each pair (byte) and alter
	for( int i = 0 ; i < hex_qstring.size()/2; i++ )
	{
		bool error[2]={true,true};
		unsigned char byte = (unsigned char)(QString(hex_qstring[2*i]).toLatin1().toInt(&error[0],16))*16;
		byte += QString(hex_qstring[(2*i)+1]).toLatin1().toInt(&error[1],16);
		
		result->insert(i,(unsigned char)QByteArray::number(byte,10).toInt()&0xFF);
		
		if( (!error[0]) | (!error[1]) )
			return 0;
	}
	
	// return success
	return 1;
	
}

void terminal_app::update_macro_button_names(void)
{
	this->m1_button->setText(this->settings->value("macro_1_name").toString());
	this->m2_button->setText(this->settings->value("macro_2_name").toString());
	this->m3_button->setText(this->settings->value("macro_3_name").toString());
	this->m4_button->setText(this->settings->value("macro_4_name").toString());
	this->m5_button->setText(this->settings->value("macro_5_name").toString());
	this->m6_button->setText(this->settings->value("macro_6_name").toString());
	this->m7_button->setText(this->settings->value("macro_7_name").toString());
	this->m8_button->setText(this->settings->value("macro_8_name").toString());
	this->m9_button->setText(this->settings->value("macro_9_name").toString());
	this->m10_button->setText(this->settings->value("macro_10_name").toString());
	this->m11_button->setText(this->settings->value("macro_11_name").toString());
	this->m12_button->setText(this->settings->value("macro_12_name").toString());
}

void terminal_app::save_gui_settings()
{
	
	this->settings->setValue("baud_rate" 	, this->get_checked_radio(this->baud_rate_group));
	this->settings->setValue("data_bits" 	, this->get_checked_radio(this->data_bits_group));
	this->settings->setValue("stop_bits" 	, this->get_checked_radio(this->stop_bits_group));
	this->settings->setValue("parity" 		, this->get_checked_radio(this->parity_group));
	this->settings->setValue("com_port" 	, this->com_port_combo->currentText());
	this->settings->setValue("hex_ascii_rx" , this->get_checked_radio(this->hex_ascii_rx));
	this->settings->setValue("hex_ascii_tx" , this->get_checked_radio(this->hex_ascii_tx));
	this->settings->setValue("autoscroll"	, this->autoscroll_check->isChecked() );

	this->settings->sync();
}
