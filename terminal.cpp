#include <QtGui> 
#include "terminal.h"
#include "qextserialenumerator.h"
#include <qextserialport.h>
#include <QStringList>
#include <QButtonGroup>
#include <QMutex>

terminal_app::terminal_app(QMainWindow *parent)
{
    setupUi(this); 			// this sets up GUI
    
    populateComPort();		// fill in the com port combo box
    
	connect_widgets();		// connect widgets with callbacks
	
	group_radio_buttons();	// group the radio buttons together
	
	// initialize variables
	this->port = 0;	
	this->comPortConnected = 0;
	
	statusbar->showMessage("Disconnected");
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
	
	// hex/ascii group
	this->hex_ascii = new QButtonGroup;
	this->hex_ascii->addButton(this->hex_radio);
	this->hex_ascii->addButton(this->ascii_radio);

}

void terminal_app::populateComPort()
{		
	// clear the com port
	this->com_port_combo->clear();    
	
	// grab the list and fill them in
	QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();    
	
	for (int i = 0; i < ports.size(); i++)
	{
		this->com_port_combo->insertItems(0, QStringList()
		#ifdef __unix__
			<< QApplication::translate("MainWindow", ports.at(i).physName.toStdString().c_str(), 0, QApplication::UnicodeUTF8) );
		#else
			<< QApplication::translate("MainWindow", ports.at(i).portName.toStdString().c_str(), 0, QApplication::UnicodeUTF8) );
		#endif
    }	
}

void terminal_app::connect_widgets()
{
	connect(this->connect_button,SIGNAL( clicked() ),this,SLOT( connect_serial_port() ));		
	connect(this->rescan_button,SIGNAL( clicked() ),this,SLOT( populateComPort() ));		
	connect(this->clear_button,SIGNAL( clicked() ),this->receive_text,SLOT( clear() ));		
	connect(this->send_button,SIGNAL( clicked() ),this,SLOT( write_to_port() ));		
}

void terminal_app::connect_serial_port()
{			
	// check if we are already connected to the com port
	if( !this->comPortConnected )
	{	
		QString comPort = this->com_port_combo->currentText();
		
		// create com port if it doesnt exist
		if( !this->port )
			this->port = new QextSerialPort(comPort);
		
		this->comPortName = comPort.toStdString();		
				
		// configure the port
		this->port->setPortName(this->comPortName.c_str());
		this->port->setBaudRate((enum BaudRateType)(get_checked_radio(this->baud_rate_group).toInt()));
		this->port->setFlowControl(FLOW_OFF);
		
		// get the acutal enum for parity
			enum ParityType parity;
			if( get_checked_radio(this->parity_group) == "none" )
				parity = PAR_NONE;
			if( get_checked_radio(this->parity_group) == "odd" )
				parity = PAR_ODD;
			if( get_checked_radio(this->parity_group) == "even" )
				parity = PAR_EVEN;		
			#if defined(Q_OS_WIN) || defined(qdoc)
			if( get_checked_radio(this->parity_group) == "mark" )
				parity = PAR_MARK;
			#endif
			if( get_checked_radio(this->parity_group) == "space" )
				parity = PAR_SPACE;
			this->port->setParity(parity);
		
		this->port->setDataBits((enum DataBitsType)(get_checked_radio(this->data_bits_group).toInt()));
		
		// get the acutal stop bits
			enum StopBitsType stop_bits;
			if( get_checked_radio(this->stop_bits_group) == "1" )
				stop_bits = STOP_1;
			if( get_checked_radio(this->stop_bits_group) == "2" )
				stop_bits = STOP_2;
			#if defined(Q_OS_WIN) || defined(qdoc)
			if( get_checked_radio(this->stop_bits_group) == "1.5" )
				stop_bits = STOP_1_5;
			#endif
			this->port->setStopBits(stop_bits);
			
		this->port->setTimeout(500);
		this->port->setQueryMode(QextSerialPort::EventDriven);
		this->port->flush();
		
		// connect receiver on serial port to onReadyRead
		connect(this->port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		
		// check for error message
		qDebug() << this->port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
		
		if (!this->port->isOpen())
		{
			qDebug("Error connecting to com port");
			statusbar->showMessage("COM Port Error! " + this->port->errorString() );
			this->comPortConnected = 0;
		}
		else
		{
			qDebug("COM port connected");
			statusbar->showMessage("Connected to " + comPort );
			
			// if a warning is present, show it
			if( this->port->errorString() != "No Error has occurred"  )
				statusbar->showMessage(QString(statusbar->currentMessage() + " WARNING: " + this->port->errorString()));
							
			this->comPortConnected = 1;			
		}		
	}
	// if we are disonnecting
	else
	{
		this->port->flush();
		delete this->port;
		this->port = 0;
		this->comPortConnected = 0;
		qDebug("COM port disconnected");
		statusbar->showMessage("Disconnected");
	}
	
	// disable the com port fields if we are connected or enable if disconnected
	toggle_com_port_fields(this->comPortConnected);
		
	//change title of connect field
	this->connect_button->setText(this->comPortConnected?"Disconnect":"Connect");
}

void terminal_app::write_to_port()
{
	if( this->comPortConnected )
	{
		this->port->write(this->transmit_field->text().toStdString().c_str(),this->transmit_field->text().size());
		this->transmit_text->insertPlainText(this->transmit_field->text());
		this->transmit_field->clear();
	}
}

QString terminal_app::get_checked_radio(QButtonGroup *group)
{
	return group->checkedButton()->text();
}

void terminal_app::onReadyRead()
{   
	QMutexLocker locker(&this->mutex);
	QByteArray bytes;
    int a = port->bytesAvailable();
    bytes.resize(a);
    this->port->read(bytes.data(), bytes.size());
    //this->mutex.lock();
    //for(int  i = 0 ; i < a; i++ )
		this->receive_text->insertPlainText(bytes);
	//this->mutex.unlock();
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
