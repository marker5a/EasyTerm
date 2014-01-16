#include <QtGui> 
#include "macro_editor.h"

macro_editor::macro_editor(terminal_app *parent)
{
    setupUi(this); 			// this sets up the dialog window
    
    this->parent = parent;
    
    // allocate memory for the qbuttongroup
    this->macro_1_hex_ascii  = new QButtonGroup;
    this->macro_2_hex_ascii  = new QButtonGroup;
	this->macro_3_hex_ascii  = new QButtonGroup;
	this->macro_4_hex_ascii  = new QButtonGroup;
	this->macro_5_hex_ascii  = new QButtonGroup;
	this->macro_6_hex_ascii  = new QButtonGroup;
	this->macro_7_hex_ascii  = new QButtonGroup;
	this->macro_8_hex_ascii  = new QButtonGroup;
	this->macro_9_hex_ascii  = new QButtonGroup;
	this->macro_10_hex_ascii = new QButtonGroup;	
	this->macro_11_hex_ascii = new QButtonGroup;
	this->macro_12_hex_ascii = new QButtonGroup;
	
	// group radio buttons appropriately
    this->macro_1_hex_ascii->addButton(  this->macro_1_hex 		);
    this->macro_1_hex_ascii->addButton(  this->macro_1_ascii 	);
	this->macro_2_hex_ascii->addButton(  this->macro_2_hex 		);
	this->macro_2_hex_ascii->addButton(  this->macro_2_ascii 	);
	this->macro_3_hex_ascii->addButton(  this->macro_3_hex 		);
	this->macro_3_hex_ascii->addButton(  this->macro_3_ascii 	);
	this->macro_4_hex_ascii->addButton(  this->macro_4_hex 		);
	this->macro_4_hex_ascii->addButton(  this->macro_4_ascii	);
	this->macro_5_hex_ascii->addButton(  this->macro_5_hex 		);
	this->macro_5_hex_ascii->addButton(  this->macro_5_ascii 	);
	this->macro_6_hex_ascii->addButton(  this->macro_6_hex 		);
	this->macro_6_hex_ascii->addButton(  this->macro_6_ascii 	);
	this->macro_7_hex_ascii->addButton(  this->macro_7_hex 		);
	this->macro_7_hex_ascii->addButton(  this->macro_7_ascii 	);
	this->macro_8_hex_ascii->addButton(  this->macro_8_hex 		);
	this->macro_8_hex_ascii->addButton(  this->macro_8_ascii 	);
	this->macro_9_hex_ascii->addButton(  this->macro_9_hex 		);
	this->macro_9_hex_ascii->addButton(  this->macro_9_ascii 	);
	this->macro_10_hex_ascii->addButton( this->macro_10_hex 	);
	this->macro_10_hex_ascii->addButton( this->macro_10_ascii 	);
	this->macro_11_hex_ascii->addButton( this->macro_11_hex 	);
	this->macro_11_hex_ascii->addButton( this->macro_11_ascii 	);
	this->macro_12_hex_ascii->addButton( this->macro_12_hex 	);
	this->macro_12_hex_ascii->addButton( this->macro_12_ascii 	);
	
	// check the hex/ascii buttons
	parent->set_checked_radio(this->macro_1_hex_ascii,parent->settings->value("macro_1_hex_ascii").toString());
	parent->set_checked_radio(this->macro_2_hex_ascii,parent->settings->value("macro_2_hex_ascii").toString());
	parent->set_checked_radio(this->macro_3_hex_ascii,parent->settings->value("macro_3_hex_ascii").toString());
	parent->set_checked_radio(this->macro_4_hex_ascii,parent->settings->value("macro_4_hex_ascii").toString());
	parent->set_checked_radio(this->macro_5_hex_ascii,parent->settings->value("macro_5_hex_ascii").toString());
	parent->set_checked_radio(this->macro_6_hex_ascii,parent->settings->value("macro_6_hex_ascii").toString());
	parent->set_checked_radio(this->macro_7_hex_ascii,parent->settings->value("macro_7_hex_ascii").toString());
	parent->set_checked_radio(this->macro_8_hex_ascii,parent->settings->value("macro_8_hex_ascii").toString());
	parent->set_checked_radio(this->macro_9_hex_ascii,parent->settings->value("macro_9_hex_ascii").toString());
	parent->set_checked_radio(this->macro_10_hex_ascii,parent->settings->value("macro_10_hex_ascii").toString());
	parent->set_checked_radio(this->macro_11_hex_ascii,parent->settings->value("macro_11_hex_ascii").toString());
	parent->set_checked_radio(this->macro_12_hex_ascii,parent->settings->value("macro_12_hex_ascii").toString());
	
	this->macro_1_name->setText(	parent->settings->value("macro_1_name").toString());
	this->macro_2_name->setText(	parent->settings->value("macro_2_name").toString());
	this->macro_3_name->setText(	parent->settings->value("macro_3_name").toString());
	this->macro_4_name->setText(	parent->settings->value("macro_4_name").toString());
	this->macro_5_name->setText(	parent->settings->value("macro_5_name").toString());
	this->macro_6_name->setText(	parent->settings->value("macro_6_name").toString());
	this->macro_7_name->setText(	parent->settings->value("macro_7_name").toString());
	this->macro_8_name->setText(	parent->settings->value("macro_8_name").toString());
	this->macro_9_name->setText(	parent->settings->value("macro_9_name").toString());
	this->macro_10_name->setText(	parent->settings->value("macro_10_name").toString());
	this->macro_11_name->setText(	parent->settings->value("macro_11_name").toString());
	this->macro_12_name->setText(	parent->settings->value("macro_12_name").toString());
	
	this->macro_1_content->setText(		parent->settings->value("macro_1_content").toString());
	this->macro_2_content->setText(		parent->settings->value("macro_2_content").toString());
	this->macro_3_content->setText(		parent->settings->value("macro_3_content").toString());
	this->macro_4_content->setText(		parent->settings->value("macro_4_content").toString());
	this->macro_5_content->setText(		parent->settings->value("macro_5_content").toString());
	this->macro_6_content->setText(		parent->settings->value("macro_6_content").toString());
	this->macro_7_content->setText(		parent->settings->value("macro_7_content").toString());
	this->macro_8_content->setText(		parent->settings->value("macro_8_content").toString());
	this->macro_9_content->setText(		parent->settings->value("macro_9_content").toString());
	this->macro_10_content->setText(	parent->settings->value("macro_10_content").toString());
	this->macro_11_content->setText(	parent->settings->value("macro_11_content").toString());
	this->macro_12_content->setText(	parent->settings->value("macro_12_content").toString());
	
	connect_widgets();
}

void macro_editor::save_macros()
{
	this->parent->settings->setValue("macro_1_name",		this->macro_1_name->text());
	this->parent->settings->setValue("macro_2_name",		this->macro_2_name->text());
	this->parent->settings->setValue("macro_3_name",		this->macro_3_name->text());
	this->parent->settings->setValue("macro_4_name",		this->macro_4_name->text());
	this->parent->settings->setValue("macro_5_name",		this->macro_5_name->text());
	this->parent->settings->setValue("macro_6_name",		this->macro_6_name->text());
	this->parent->settings->setValue("macro_7_name",		this->macro_7_name->text());
	this->parent->settings->setValue("macro_8_name",		this->macro_8_name->text());
	this->parent->settings->setValue("macro_9_name",		this->macro_9_name->text());
	this->parent->settings->setValue("macro_10_name",		this->macro_10_name->text());
	this->parent->settings->setValue("macro_11_name",		this->macro_11_name->text());
	this->parent->settings->setValue("macro_12_name",		this->macro_12_name->text());		
	
	this->parent->settings->setValue("macro_1_content",	this->macro_1_content->text());
	this->parent->settings->setValue("macro_2_content",	this->macro_2_content->text());
	this->parent->settings->setValue("macro_3_content",	this->macro_3_content->text());
	this->parent->settings->setValue("macro_4_content",	this->macro_4_content->text());
	this->parent->settings->setValue("macro_5_content",	this->macro_5_content->text());
	this->parent->settings->setValue("macro_6_content",	this->macro_6_content->text());
	this->parent->settings->setValue("macro_7_content",	this->macro_7_content->text());
	this->parent->settings->setValue("macro_8_content",	this->macro_8_content->text());
	this->parent->settings->setValue("macro_9_content",	this->macro_9_content->text());
	this->parent->settings->setValue("macro_10_content",	this->macro_10_content->text());
	this->parent->settings->setValue("macro_11_content",	this->macro_11_content->text());
	this->parent->settings->setValue("macro_12_content",	this->macro_12_content->text());	
	
	this->parent->settings->sync();
	
	this->close();
	
}

void macro_editor::connect_widgets()
{
	connect(this->button_box,SIGNAL( accepted() ) , this , SLOT( save_macros() ) );
	connect(this->button_box,SIGNAL( rejected() ) , this , SLOT( close() ) );
}
