#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "CheckBox.h"
#include<fstream>
#include <limits>
#include <sstream>
#include<cctype>

class States {
	public:
		//constructor / destructor
		States() {}
		~States() {}
		
		//State manager, 1 = Menu, 2 = Projectile Motion, 3 = Collisions
		int CurrentState;

		//Window Settings
		int xWinSize;
		int yWinSize;
		sf::RenderWindow window;
		sf::Image Icon;

		//Menu Assets
		bool MenuRanOnce = false;
		bool eqranonce = false;

		sf::Texture TitleTexture;
		sf::Texture PMBTexture;
		sf::Texture CBTexture;

		sf::Sprite Title;
		sf::Sprite PMB;
		sf::Sprite CB;
		
		//Projectile motion Assets
		bool ProjectileMotionRanOnce = false;
		int showadvancedmenu = -1;
		int showhelp = -1;

		
		sf::Texture Trig;
		sf::Sprite horizTrig;
		sf::Sprite vertTrig;
		sf::Sprite resTrig;

		sf::Text MassofObject;

		float verticalVelocitybefore;


		float scaleVariable;

		float horizontalVelocity;
		float horizontalDisplacement;

		float verticalDisplacement;
		float verticalInitialVelocity;
		float verticalFinalVelocity;
		float verticalAcceleration;

		int frameTimer;

		bool setValues1;
		bool setValues2;

		sf::RectangleShape HelpBack;
		sf::RectangleShape HelpBorder;
		sf::Texture CloseButtonHelpTexture;
		sf::Sprite CloseButtonHelp;
		
		sf::Sprite ResetSim;
		sf::Texture ResetSimTexture;

		sf::Sprite AccelerationArrow;
		sf::Texture AccelerationArrowTexture;

		std::vector<sf::Vertex> lineSegments;

		sf::Vector2f originalPosition;

		sf::Text AccelerationText;

		sf::Sprite ForceArrow;
		sf::Texture ForceArrowTexture;
		sf::Text ForceArrowText;


		sf::RectangleShape HorizontalVelocityArrow;
		sf::RectangleShape VerticalVelocityArrow;
		sf::RectangleShape ResultantVelocityArrow;

		CheckBox TraceMotion;
		CheckBox VelocityVector;
		CheckBox AccelerationVector;
		CheckBox ForceVector;

		sf::Text showDirection;

		sf::CircleShape ObjectInMotion;
		sf::CircleShape MaximumPoint;
		sf::CircleShape EndLocation;


		sf::Texture eq1texture;
		sf::Texture eq2texture;
		sf::Texture rearrange1texture;
		sf::Texture rearrange2texture;
		sf::Text eqtext;

		sf::Sprite eq1;
		sf::Sprite eq2;
		sf::Sprite rearrange1;
		sf::Sprite rearrange2;


		sf::RectangleShape advancedBack;
		sf::RectangleShape backforadvancedback;

		sf::Texture RightArrowTexture;
		sf::Texture LeftArrowTexture;

		sf::Text HorizontalDisplayText;
		sf::RectangleShape HorizontalArrowBox;
		sf::Sprite HorizontalRightArrow;
		sf::Sprite HorizontalLeftArrow;

		sf::Text VerticalDisplayText;
		sf::RectangleShape VerticalArrowBox;
		sf::Sprite VerticalRightArrow;
		sf::Sprite VerticalLeftArrow;

		sf::Texture BackgroundTexture;
		sf::Sprite Background;
		
		sf::RectangleShape BackBorderforborder;

		sf::Texture advancedclosetexture;
		sf::Sprite AdvancedClose;

		sf::Text Verticaltxt;
		sf::Text Horizontaltxt;

		sf::Text FullScreenOnly;

		Button Displacement;
		Button InitialVelocity;
		Button FinalVelocity;
		Button Acceleration;
		Button Time;

		Button HDisplacement;
		Button HVelocity;

		sf::Texture AdvancedTexture;
		sf::Sprite Advanced;

		sf::Texture HelpTexture;
		sf::Sprite Help;

		//Collision Assets
		bool CollisionRanOnce = false;

		float maxelasticity;
		float elasticity;

		
		sf::CircleShape rcircle;
		sf::CircleShape bcircle;

		Button Mass1;
		Button Mass2;

		Button Velocity1;
		Button Velocity2;

		sf::Texture RunButtonTexture;
		sf::Sprite RunButton;

		sf::Texture ResetButtonTexture;
		sf::Sprite ResetButton;

		sf::Texture ImportButtonTexture;
		sf::Sprite ImportButton;
		sf::Texture DownloadButtonTexture;
		sf::Sprite DownloadButton;

		sf::Texture CloseButtonTexture;
		sf::Sprite CloseButton;
		sf::Texture SaveButtonTexture;
		sf::Sprite SaveButton;
		

		sf::Text elasticitytxt;
		sf::Text elasticitydisplay;
		sf::Text successsave;
		sf::Text NotRunError;
		sf::Text MassError;
		sf::Text SuccessImport;

		std::string filenameholder;

		bool showsaved;
		bool showrunerror;
		bool showmasserror;
		bool showimporterror;
		bool showsuccess;
		int timer;
		int timer2;
		int timer3;
		int timer4;
		int timer5;
		sf::RectangleShape sliderbackborder;
		sf::RectangleShape sliderbox;
		bool mousepressslider = false;



		std::fstream filehandler;

		bool run;
		
		

		float velocity1;
		float velocity2;

		float momentum1;
		float momentum2;

		bool singlecollision = false;

		sf::Text Velocity1Out;
		sf::Text Velocity2Out;

		sf::Text Direction;



		sf::RectangleShape BackBorder;
		
		//General Assets
		sf::Font font;

		sf::Texture BackButtonTexture;

		sf::Sprite BackButton;

		Button DownloadInput;
		Button ImportInput;
		int ShowDownloadUI;
		int ShowImportUI;
		sf::RectangleShape BackBoxDownload;
		sf::RectangleShape BackBorderDownload;

		sf::RectangleShape BackBoxImport;
		sf::RectangleShape BackBorderImport;

		sf::Texture ImportCloseButtonTexture;
		sf::Sprite ImportCloseButton;

		sf::Texture ConfirmTexture;
		sf::Sprite Confirm;

		

		sf::Text TxtNotFound;

		//Mouse settings
		sf::Cursor cursor;
		sf::Vector2f worldPos;
		

		//sf::RenderWindow window(sf::VideoMode(xWinPos, yWinPos), "Kinemechanics");
		void start(int x, int y);
		bool menustate();
		bool projectilemotionstate();
		bool collisionstate();
private:
	void textmaker(sf::Text &object,const sf::Font &font,const sf::String InputString, int size, sf::Vector2f position, sf::Color color, sf::Uint32 style);
	void buttonmaker(sf::Sprite &object,std::string textureloc, sf::Texture &texture, sf::Vector2f position, sf::Vector2f size, sf::Color color);
	std::string getLineFromFile(const std::string& filename, int lineNumber);
	float extractFloatFromString(const std::string& inputString);
	int QuestionType();
};
