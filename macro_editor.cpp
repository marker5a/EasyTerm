#include <QtGui> 
#include "macro_editor.h"

macro_editor::macro_editor(terminal_app *parent)
{
    setupUi(this); 			// this sets up the dialog window
    
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
	
	this->macro_1_name->setText("M1");
	this->macro_2_name->setText("M2");
	this->macro_3_name->setText("M3");
	this->macro_4_name->setText("M4");
	this->macro_5_name->setText("M5");
	this->macro_6_name->setText("M6");
	this->macro_7_name->setText("M7");
	this->macro_8_name->setText("M8");
	this->macro_9_name->setText("M9");
	this->macro_10_name->setText("M10");
	this->macro_11_name->setText("M11");
	this->macro_12_name->setText("M12");
	
	
}
