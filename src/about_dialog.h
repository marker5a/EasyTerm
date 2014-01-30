/*
 * about_dialog.h is part of EasyTerm, and is Copyright Christopher M
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

#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include "ui_about.h"

class about_dialog : public QDialog, public Ui::About
{
    Q_OBJECT
 
public:
    about_dialog();

}; 

#endif
