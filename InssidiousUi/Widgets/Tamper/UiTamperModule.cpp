#include "UiTamperModule.h"

#include "UiTamperSpeed.h"
#include "UiTamperConditions.h"
#include "UiTamperFirewall.h"
#include "UiTamperDamage.h"


#include "UiTamperNoInternet.h"
#include "UiTamperNoServer.h"
#include "UiTamperNoWebContent.h"
#include "UiTamperWebServiceFailures.h"


static QString TamperTypeName[NUM_TAMPER_TYPES]
{
	QString("Network Speed"),
	QString("Network Conditions"),
	QString("Network Firewall"),
	QString("Network Damage"),
	QString("No Internet"),
	QString("Block Servers"),
	QString("Block Web Content (Coming Soon)"),
	QString("Web Service Failures (Coming Soon)")
};

static QString TamperTypeDescription[NUM_TAMPER_TYPES]
{
	QString("Cap the speed of the network connection."),
	QString("Introduce intermittent noise to the network connection."),
	QString("Replicate restrictive network connections."),
	QString("Intentionally damage traffic to generate interesting errors."),
	QString("Test functionality without internet access."),
	QString("Test functionality when servers are unreachable."),
	QString("Test functionality when web requests time out."),
	QString("Reply to web requests with specific errors.")
};

UiTamperModule::UiTamperModule(QWidget* parent, TamperType tamperType)
	: QWidget(parent)
{

	/* Set the layout and initial settings */

	moduleLayout = new QVBoxLayout();
	moduleLayout->setMargin(0);
	moduleLayout->setSpacing(0);
	moduleLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	
	this->setLayout(moduleLayout);
	this->setFixedWidth(380);
	this->setFixedHeight(120);
	this->setAutoFillBackground(true);
	

	/* Initialize the button palettes for the various states */

	moduleBackgroundPaletteActive.setBrush(QPalette::Background, QBrush(moduleImageActive));
	moduleBackgroundPaletteActiveHover.setBrush(QPalette::Background, QBrush(moduleImageActiveHover));
	moduleBackgroundPaletteActivePressed.setBrush(QPalette::Background, QBrush(moduleImageActivePressed));
	moduleBackgroundPaletteInactive.setBrush(QPalette::Background, QBrush(moduleImageInactive));
	moduleBackgroundPaletteInactiveHover.setBrush(QPalette::Background, QBrush(moduleImageInactiveHover));
	moduleBackgroundPaletteInactivePressed.setBrush(QPalette::Background, QBrush(moduleImageInactivePressed));


	/* Initialize the module name, font, and text palettes */

	moduleNameFont.setFamily("Segoe UI");
	moduleNameFont.setPixelSize(16);
	moduleNameFont.setStyleStrategy(QFont::PreferAntialias);

	moduleTextFont.setFamily("Segoe UI");
	moduleTextFont.setPixelSize(12);
	moduleTextFont.setStyleStrategy(QFont::PreferAntialias);

	moduleTextPalette.setColor(QPalette::WindowText, QColor(51, 51, 51));


	/* Add the Module Name and Description to the layout */

	moduleNameLabel = new QLabel(TamperTypeName[tamperType]);
	moduleNameLabel->setContentsMargins(0, 10, 0, 0);
	moduleNameLabel->setAlignment(Qt::AlignHCenter);
	moduleNameLabel->setFont(moduleNameFont);
	moduleNameLabel->setPalette(moduleTextPalette);

	moduleDescriptionLabel = new QLabel(TamperTypeDescription[tamperType]);
	moduleDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	moduleDescriptionLabel->setAlignment(Qt::AlignHCenter);
	moduleDescriptionLabel->setFont(moduleTextFont);
	moduleDescriptionLabel->setPalette(moduleTextPalette);

	moduleLayout->addWidget(moduleNameLabel);
	moduleLayout->addWidget(moduleDescriptionLabel);


	/* Start as an inactive button */

	this->setPalette(moduleBackgroundPaletteInactive);

}

UiTamperModule* UiTamperModule::makeUiTamperModule(QWidget* parent, TamperType tamperType)
{
	switch (tamperType)
	{
		/* scenarios */
		
		case SPEED:
			return new UiTamperSpeed(parent, tamperType);
		case CONDITIONS:
			return new UiTamperConditions(parent, tamperType);
		case FIREWALL:
			return new UiTamperFirewall(parent, tamperType);
		case DAMAGE:
			return new UiTamperDamage(parent, tamperType);


		/* failures */

		case NO_INTERNET:
			return new UiTamperNoInternet(parent, tamperType);
		case NO_SERVER:
			return new UiTamperNoServer(parent, tamperType);
		case NO_WEB_CONTENT:
			return new UiTamperNoWebContent(parent, tamperType);
		case WEBSERVICE_FAILURES:
			return new UiTamperWebServiceFailures(parent, tamperType);


		/* Should never reach */

		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}


void UiTamperModule::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == moduleBackgroundPaletteActivePressed.background())
	{
		this->setActive(false);
	}
	else if (this->palette().background() == moduleBackgroundPaletteInactivePressed.background())
	{
		this->setActive(true);
	}
}

void UiTamperModule::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == moduleBackgroundPaletteActive.background() || this->palette().background() == moduleBackgroundPaletteActiveHover.background())
		{
			this->setPalette(moduleBackgroundPaletteActivePressed);
		}
		else if (this->palette().background() == moduleBackgroundPaletteInactive.background() || this->palette().background() == moduleBackgroundPaletteInactiveHover.background())
		{
			this->setPalette(moduleBackgroundPaletteInactivePressed);
		}
	}
}


void UiTamperModule::enterEvent(QEvent *e)
{
	if (this->palette().background() == moduleBackgroundPaletteActive.background())
	{
		this->setPalette(moduleBackgroundPaletteActiveHover);
	}
	else if (this->palette().background() == moduleBackgroundPaletteInactive.background())
	{
		this->setPalette(moduleBackgroundPaletteInactiveHover);
	}
}


void UiTamperModule::leaveEvent(QEvent *e)
{
	if (this->palette().background() == moduleBackgroundPaletteActiveHover.background() || this->palette().background() == moduleBackgroundPaletteActivePressed.background())
	{
		this->setPalette(moduleBackgroundPaletteActive);
	}
	else if (this->palette().background() == moduleBackgroundPaletteInactiveHover.background() || this->palette().background() == moduleBackgroundPaletteInactivePressed.background())
	{
		this->setPalette(moduleBackgroundPaletteInactive);
	}
}