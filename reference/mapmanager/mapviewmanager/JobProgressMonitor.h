/*
MapManager library for the conversion, manipulation and analysis 
of maps used in Mobile Robotics research.
Copyright (C) 2005 Shane O'Sullivan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

email: shaneosullivan1@gmail.com
*/

#ifndef JOBPROGRESSMONITOR_H
#define JOBPROGRESSMONITOR_H

//This is an interface class that can be used by progress monitors, such as dialogs
//that pop up to report the percentage completion of a large job

class JobProgressMonitor
{
public:
	virtual void setPercentageComplete(double perc) = 0;
	virtual void start() = 0;
	virtual void setFinished() = 0;

	virtual bool jobCompleted() = 0;

	virtual void setCaption(char* caption)=0;//{/*default implementation does nothing*/};
};


#endif