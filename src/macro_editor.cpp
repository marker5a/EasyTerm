/*
 * macro_editor.cpp is part of EasyTerm, and is Copyright Christopher M
 * Hamilton (marker5a@gmail.com), 2014.
 *
 * EasyTerm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * EasyTerm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtWidgets> 
#include "macro_editor.h"

macro_editor::macro_editor(terminal_app *parent)
{
    setupUi(this); 			// this sets up the dialog window
    
    this->parent = parent;
}

void macro_editor::save_macros()
{
	// save macro names into settings
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
	
	// save macro contents into settings
	this->parent->settings->setValue("macro_1_content",	this->macro_1_content->text());
	this->parent->settings->setValue("macro_2_content",	this->macro_2_content->text());
	this->parent->settings->setValue("macro_3_content",	this->macro_3_content->text());
	this->parent->settings->setValue("macro_4_content",	this->macro_4_content->text());
	this->parent->settings->setValue("macro_5_content",	this->macro_5_content->text());
	this->parent->settings->setValue("macro_6_content",	this->macro_6_content->text());
	this->parent->settings->setValue("macro_7_content",	this->macro_7_content->text());
	this->parent->settings->setValue("macro_8_content",	this->macro_8_content->text());
	this->parent->settings->setValue("macro_9_content",	this->macro_9_content->text());
	this->parent->settings->setValue("macro_10_content",this->macro_10_content->text());
	this->parent->settings->setValue("macro_11_content",this->macro_11_content->text());
	this->parent->settings->setValue("macro_12_content",this->macro_12_content->text());
		

	// save the hex ascii settings of the macros
	this->parent->settings->setValue("macro_1_hex_ascii" , parent->get_checked_radio(this->macro_1_hex_ascii));
	this->parent->settings->setValue("macro_2_hex_ascii" , parent->get_checked_radio(this->macro_2_hex_ascii));
	this->parent->settings->setValue("macro_3_hex_ascii" , parent->get_checked_radio(this->macro_3_hex_ascii));
	this->parent->settings->setValue("macro_4_hex_ascii" , parent->get_checked_radio(this->macro_4_hex_ascii));
	this->parent->settings->setValue("macro_5_hex_ascii" , parent->get_checked_radio(this->macro_5_hex_ascii));
	this->parent->settings->setValue("macro_6_hex_ascii" , parent->get_checked_radio(this->macro_6_hex_ascii));
	this->parent->settings->setValue("macro_7_hex_ascii" , parent->get_checked_radio(this->macro_7_hex_ascii));
	this->parent->settings->setValue("macro_8_hex_ascii" , parent->get_checked_radio(this->macro_8_hex_ascii));
	this->parent->settings->setValue("macro_9_hex_ascii" , parent->get_checked_radio(this->macro_9_hex_ascii));
	this->parent->settings->setValue("macro_10_hex_ascii", parent->get_checked_radio(this->macro_10_hex_ascii));
	this->parent->settings->setValue("macro_11_hex_ascii", parent->get_checked_radio(this->macro_11_hex_ascii));
	this->parent->settings->setValue("macro_12_hex_ascii", parent->get_checked_radio(this->macro_12_hex_ascii));

	// save the newline settings of the macros
	this->parent->settings->setValue("macro_1_newline" , this->macro_1_newline->isChecked());
	this->parent->settings->setValue("macro_2_newline" , this->macro_2_newline->isChecked());
	this->parent->settings->setValue("macro_3_newline" , this->macro_3_newline->isChecked());
	this->parent->settings->setValue("macro_4_newline" , this->macro_4_newline->isChecked());
	this->parent->settings->setValue("macro_5_newline" , this->macro_5_newline->isChecked());
	this->parent->settings->setValue("macro_6_newline" , this->macro_6_newline->isChecked());
	this->parent->settings->setValue("macro_7_newline" , this->macro_7_newline->isChecked());
	this->parent->settings->setValue("macro_8_newline" , this->macro_8_newline->isChecked());
	this->parent->settings->setValue("macro_9_newline" , this->macro_9_newline->isChecked());
	this->parent->settings->setValue("macro_10_newline", this->macro_10_newline->isChecked());
	this->parent->settings->setValue("macro_11_newline", this->macro_11_newline->isChecked());
	this->parent->settings->setValue("macro_12_newline", this->macro_12_newline->isChecked());

	this->parent->settings->setValue("macro_1_crlf" , parent->get_checked_radio(this->macro_1_crlf));
	this->parent->settings->setValue("macro_2_crlf" , parent->get_checked_radio(this->macro_2_crlf));
	this->parent->settings->setValue("macro_3_crlf" , parent->get_checked_radio(this->macro_3_crlf));
	this->parent->settings->setValue("macro_4_crlf" , parent->get_checked_radio(this->macro_4_crlf));
	this->parent->settings->setValue("macro_5_crlf" , parent->get_checked_radio(this->macro_5_crlf));
	this->parent->settings->setValue("macro_6_crlf" , parent->get_checked_radio(this->macro_6_crlf));
	this->parent->settings->setValue("macro_7_crlf" , parent->get_checked_radio(this->macro_7_crlf));
	this->parent->settings->setValue("macro_8_crlf" , parent->get_checked_radio(this->macro_8_crlf));
	this->parent->settings->setValue("macro_9_crlf" , parent->get_checked_radio(this->macro_9_crlf));
	this->parent->settings->setValue("macro_10_crlf", parent->get_checked_radio(this->macro_10_crlf));
	this->parent->settings->setValue("macro_11_crlf", parent->get_checked_radio(this->macro_11_crlf));
	this->parent->settings->setValue("macro_12_crlf", parent->get_checked_radio(this->macro_12_crlf));
	
	// synchronize the settings
	this->parent->settings->sync();
	
	// close the dialog
	this->close();
	
}

void macro_editor::connect_widgets()
{
	connect(this->button_box,SIGNAL( accepted() ) , this , SLOT( save_macros() ) );
	connect(this->button_box,SIGNAL( rejected() ) , this , SLOT( close() ) );
}

void macro_editor::group_radio_buttons(void)
{
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
	
	this->macro_1_crlf  = new QButtonGroup;
	this->macro_2_crlf  = new QButtonGroup;
	this->macro_3_crlf  = new QButtonGroup;
	this->macro_4_crlf  = new QButtonGroup;
	this->macro_5_crlf  = new QButtonGroup;
	this->macro_6_crlf  = new QButtonGroup;
	this->macro_7_crlf  = new QButtonGroup;
	this->macro_8_crlf  = new QButtonGroup;
	this->macro_9_crlf  = new QButtonGroup;
	this->macro_10_crlf = new QButtonGroup;
	this->macro_11_crlf = new QButtonGroup;
	this->macro_12_crlf = new QButtonGroup;
	
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
	
	this->macro_1_crlf->addButton( this->macro1_cr );
	this->macro_1_crlf->addButton( this->macro1_lf );
	this->macro_1_crlf->addButton( this->macro1_crlf );
	this->macro_2_crlf->addButton( this->macro2_cr );
	this->macro_2_crlf->addButton( this->macro2_lf );
	this->macro_2_crlf->addButton( this->macro2_crlf );
	this->macro_3_crlf->addButton( this->macro3_cr );
	this->macro_3_crlf->addButton( this->macro3_lf );
	this->macro_3_crlf->addButton( this->macro3_crlf );
	this->macro_4_crlf->addButton( this->macro4_cr );
	this->macro_4_crlf->addButton( this->macro4_lf );
	this->macro_4_crlf->addButton( this->macro4_crlf );
	this->macro_5_crlf->addButton( this->macro5_cr );
	this->macro_5_crlf->addButton( this->macro5_lf );
	this->macro_5_crlf->addButton( this->macro5_crlf );
	this->macro_6_crlf->addButton( this->macro6_cr );
	this->macro_6_crlf->addButton( this->macro6_lf );
	this->macro_6_crlf->addButton( this->macro6_crlf );
	this->macro_7_crlf->addButton( this->macro7_cr );
	this->macro_7_crlf->addButton( this->macro7_lf );
	this->macro_7_crlf->addButton( this->macro7_crlf );
	this->macro_8_crlf->addButton( this->macro8_cr );
	this->macro_8_crlf->addButton( this->macro8_lf );
	this->macro_8_crlf->addButton( this->macro8_crlf );
	this->macro_9_crlf->addButton( this->macro9_cr );
	this->macro_9_crlf->addButton( this->macro9_lf );
	this->macro_9_crlf->addButton( this->macro9_crlf );
	this->macro_10_crlf->addButton( this->macro10_cr );
	this->macro_10_crlf->addButton( this->macro10_lf );
	this->macro_10_crlf->addButton( this->macro10_crlf );
	this->macro_11_crlf->addButton( this->macro11_cr );
	this->macro_11_crlf->addButton( this->macro11_lf );
	this->macro_11_crlf->addButton( this->macro11_crlf );
	this->macro_12_crlf->addButton( this->macro12_cr );
	this->macro_12_crlf->addButton( this->macro12_lf );
	this->macro_12_crlf->addButton( this->macro12_crlf );
}

void macro_editor::load_settings()
{
	// default radios
	parent->set_checked_radio(this->macro_1_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_2_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_3_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_4_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_5_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_6_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_7_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_8_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_9_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_10_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_11_hex_ascii, "Hex");
	parent->set_checked_radio(this->macro_12_hex_ascii, "Hex");
	
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
	
	// default radios
	parent->set_checked_radio(this->macro_1_crlf, "CR");
	parent->set_checked_radio(this->macro_2_crlf, "CR");
	parent->set_checked_radio(this->macro_3_crlf, "CR");
	parent->set_checked_radio(this->macro_4_crlf, "CR");
	parent->set_checked_radio(this->macro_5_crlf, "CR");
	parent->set_checked_radio(this->macro_6_crlf, "CR");
	parent->set_checked_radio(this->macro_7_crlf, "CR");
	parent->set_checked_radio(this->macro_8_crlf, "CR");
	parent->set_checked_radio(this->macro_9_crlf, "CR");
	parent->set_checked_radio(this->macro_10_crlf, "CR");
	parent->set_checked_radio(this->macro_11_crlf, "CR");
	parent->set_checked_radio(this->macro_12_crlf, "CR");
	
	parent->set_checked_radio(this->macro_1_crlf,parent->settings->value("macro_1_crlf").toString());
	parent->set_checked_radio(this->macro_2_crlf,parent->settings->value("macro_2_crlf").toString());
	parent->set_checked_radio(this->macro_3_crlf,parent->settings->value("macro_3_crlf").toString());
	parent->set_checked_radio(this->macro_4_crlf,parent->settings->value("macro_4_crlf").toString());
	parent->set_checked_radio(this->macro_5_crlf,parent->settings->value("macro_5_crlf").toString());
	parent->set_checked_radio(this->macro_6_crlf,parent->settings->value("macro_6_crlf").toString());
	parent->set_checked_radio(this->macro_7_crlf,parent->settings->value("macro_7_crlf").toString());
	parent->set_checked_radio(this->macro_8_crlf,parent->settings->value("macro_8_crlf").toString());
	parent->set_checked_radio(this->macro_9_crlf,parent->settings->value("macro_9_crlf").toString());
	parent->set_checked_radio(this->macro_10_crlf,parent->settings->value("macro_10_crlf").toString());
	parent->set_checked_radio(this->macro_11_crlf,parent->settings->value("macro_11_crlf").toString());
	parent->set_checked_radio(this->macro_12_crlf,parent->settings->value("macro_12_crlf").toString());
	
	
	this->macro_1_newline->setCheckState(( parent->settings->value("macro_1_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_2_newline->setCheckState(( parent->settings->value("macro_2_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_3_newline->setCheckState(( parent->settings->value("macro_3_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_4_newline->setCheckState(( parent->settings->value("macro_4_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_5_newline->setCheckState(( parent->settings->value("macro_5_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_6_newline->setCheckState(( parent->settings->value("macro_6_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_7_newline->setCheckState(( parent->settings->value("macro_7_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_8_newline->setCheckState(( parent->settings->value("macro_8_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_9_newline->setCheckState(( parent->settings->value("macro_9_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_10_newline->setCheckState(( parent->settings->value("macro_10_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_11_newline->setCheckState(( parent->settings->value("macro_11_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	this->macro_12_newline->setCheckState(( parent->settings->value("macro_12_newline").toString() == "true" ) ? Qt::Checked : Qt::Unchecked);
	
	//this->macro_2_newline->setChecked(parent->settings->value("macro_2_newline").toString()=="true" : 1 : 0);
	//this->macro_3_newline->setChecked(parent->settings->value("macro_3_newline").toString()=="true" : 1 : 0);
	//this->macro_4_newline->setChecked(parent->settings->value("macro_4_newline").toString()=="true" : 1 : 0);
	//this->macro_5_newline->setChecked(parent->settings->value("macro_5_newline").toString()=="true" : 1 : 0);
	//this->macro_6_newline->setChecked(parent->settings->value("macro_6_newline").toString()=="true" : 1 : 0);
	//this->macro_7_newline->setChecked(parent->settings->value("macro_7_newline").toString()=="true" : 1 : 0);
	//this->macro_8_newline->setChecked(parent->settings->value("macro_8_newline").toString()=="true" : 1 : 0);
	//this->macro_9_newline->setChecked(parent->settings->value("macro_9_newline").toString()=="true" : 1 : 0);
	//this->macro_10_newline->setChecked(parent->settings->value("macro_10_newline").toString()=="true" : 1 : 0);
	//this->macro_11_newline->setChecked(parent->settings->value("macro_11_newline").toString()=="true" : 1 : 0);
	//this->macro_12_newline->setChecked(parent->settings->value("macro_12_newline").toString()=="true" : 1 : 0);
	
	// set default macro names if not defined in settings yet
	if( !parent->settings->contains("macro_1_name") )
		parent->settings->setValue("macro_1_name","M1");
	if( !parent->settings->contains("macro_2_name") )
		parent->settings->setValue("macro_2_name","M2");
	if( !parent->settings->contains("macro_3_name") )
		parent->settings->setValue("macro_3_name","M3");
	if( !parent->settings->contains("macro_4_name") )
		parent->settings->setValue("macro_4_name","M4");
	if( !parent->settings->contains("macro_5_name") )
		parent->settings->setValue("macro_5_name","M5");
	if( !parent->settings->contains("macro_6_name") )
		parent->settings->setValue("macro_6_name","M6");
	if( !parent->settings->contains("macro_7_name") )
		parent->settings->setValue("macro_7_name","M7");
	if( !parent->settings->contains("macro_8_name") )
		parent->settings->setValue("macro_8_name","M8");
	if( !parent->settings->contains("macro_9_name") )
		parent->settings->setValue("macro_9_name","M9");
	if( !parent->settings->contains("macro_10_name") )
		parent->settings->setValue("macro_10_name","M10");
	if( !parent->settings->contains("macro_11_name") )
		parent->settings->setValue("macro_11_name","M11");
	if( !parent->settings->contains("macro_12_name") )
		parent->settings->setValue("macro_12_name","M12");
	
	// set macro names from settings
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
	
	// set macro content from settings
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
}

void macro_editor::reset_cursor_positions()
{	
	// set cursor for macros back to zero
	this->macro_1_content->setCursorPosition(0);
	this->macro_2_content->setCursorPosition(0);
	this->macro_3_content->setCursorPosition(0);
	this->macro_4_content->setCursorPosition(0);
	this->macro_5_content->setCursorPosition(0);
	this->macro_6_content->setCursorPosition(0);
	this->macro_7_content->setCursorPosition(0);
	this->macro_8_content->setCursorPosition(0);
	this->macro_9_content->setCursorPosition(0);
	this->macro_10_content->setCursorPosition(0);
	this->macro_11_content->setCursorPosition(0);
	this->macro_12_content->setCursorPosition(0);
	
}
