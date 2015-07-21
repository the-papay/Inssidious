#ifndef TAB_H
#define TAB_H

#include <QtWidgets/QWidget>				//QWidgets
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWidgets/QLabel>
#include <QtGui/QMouseEvent>


class Tab : public QWidget
{
	Q_OBJECT

public:
	Tab(QWidget *parent, QString MACaddress);
	void select();
	void unselect();

	QString MAC;
	bool active;

signals:
	void tabClicked(Tab*);

private:
	void mousePressEvent(QMouseEvent *e);		//Catch mouse click events
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);



	QWidget* tabTamperContainer;



	QLabel tabDeviceIconLabel;							//QLabel for the device icon
	QLabel tabDeviceNameLabel;							//QLabel for the device name
	QLabel tabTamperCount;								//Count of active tamper items

	QString tabDeviceNameText;							//QString for device name

	QPixmap tabDeviceIconActive;						//QPixmap for active icon
	QPixmap tabDeviceIconInactive;						//QPixmap for inactive icon





	QPalette tabPaletteActive;
	QPalette tabPaletteActiveHover;
	QPalette tabPaletteActivePressed;
	QPalette tabPaletteInactive;
	QPalette tabPaletteInactiveHover;
	QPalette tabPaletteInactivePressed;

	QPixmap tabImageActive = QPixmap(":/Tabs/TabActive.png");					//QPixmap for active device tabs 
	QPixmap tabImageActiveHover = QPixmap(":/Tabs/TabActiveHover.png");			//QPixmap for active device tabs  while hovered over
	QPixmap tabImageActivePressed = QPixmap(":/Tabs/TabActivePressed.png");		//QPixmap for active device tabs while pressed
	QPixmap tabImageInactive = QPixmap(":/Tabs/TabInactive.png");				//QPixmap for inactive device tabs 
	QPixmap tabImageInactiveHover = QPixmap(":/Tabs/TabInactiveHover.png");		//QPixmap for active device tabs while hovered over
	QPixmap tabImageInactivePressed = QPixmap(":/Tabs/TabInactivePressed.png");	//QPixmap for active device tabs while pressed



};

#endif // TAB_H