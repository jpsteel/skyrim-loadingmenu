import Components.Meter;
import Shared.GlobalFunc;
import gfx.io.GameDelegate;
import gfx.ui.InputDetails;
import gfx.managers.FocusHandler;
import gfx.ui.NavigationCode;
import skse;

class LoadingMenu extends MovieClip
{
	#include "../version.as"

	var LevelMeterRect:MovieClip;
	var LevelMeter_mc:Meter;
	var LoadingText:TextField;
	var LoadingTextFader:MovieClip;
	var ContinueButtonFader:MovieClip;
	var LocationFader:MovieClip;
	var LocationText:TextField;
	var LocationBackground:MovieClip;
	var PrevButton:MovieClip;
	var NextButton:MovieClip;
	var bFadedIn:Boolean;
	var MessagesMemory = new Array();
	var memoryIndex:Number;

	function LoadingMenu()
	{
		super();
		FocusHandler.instance.setFocus(this,0);

		LoadingText = LoadingTextFader.LoadingText.textField;
		LocationText = LocationFader.textField;
		LocationBackground = LocationFader.background;
		PrevButton = LoadingTextFader.LoadingText.prevButton;
		NextButton = LoadingTextFader.LoadingText.nextButton;
		MessagesMemory = [];
		memoryIndex = 0;
		bFadedIn = false;
	}

	function InitExtensions()
	{
		GlobalFunc.SetLockFunction();
		LevelMeterRect.Lock("TL");
		//LoadingTextFader.Lock("BR");
		ContinueButtonFader.Lock("BR");
		LocationFader.Lock("TR");
		ContinueButtonFader.continueButton.gotoAndStop(276);
		ContinueButtonFader._visible = false;
		LoadingText.textAutoSize = "shrink";
		LoadingText.verticalAlign = "center";
		LoadingText.SetText(" ");
		LevelMeter_mc = new Meter(LevelMeterRect.LevelProgressBar);
	}

	function handleInput(details:InputDetails, pathToFocus:Array):Boolean
	{
		var bHandledInput:Boolean = false;
		if (GlobalFunc.IsKeyPressed(details) && bFadedIn)
		{
			if (details.navEquivalent == NavigationCode.GAMEPAD_R1 || details.code == 81)
			{
				//skse.SendModEvent("PlaySound","UIMenuPrevNext");
				if (memoryIndex >= MessagesMemory.length - 1)
				{
					MessagesMemory[memoryIndex] = LoadingText.text;
					memoryIndex = MessagesMemory.length;
					refreshLoadingText();
				}
				else
				{
					SetLoadingText(MessagesMemory[memoryIndex + 1]);
					memoryIndex += 1;
				}
				bHandledInput = true;
			}
			else if (details.navEquivalent == NavigationCode.GAMEPAD_L1 || details.code == 82)
			{
				//skse.SendModEvent("PlaySound","UIMenuPrevNext");
				if (memoryIndex == 0)
				{
					MessagesMemory[0] = LoadingText.text;
					refreshLoadingText();
					MessagesMemory.unshift(LoadingText.text);
				}
				else
				{
					MessagesMemory[memoryIndex] = LoadingText.text;
					SetLoadingText(MessagesMemory[memoryIndex - 1]);
					memoryIndex -= 1;
				}
				bHandledInput = true;
			}
			/*else if (details.navEquivalent == NavigationCode.ENTER && ContinueButtonFader._visible == true){
				ContinueButtonFader._visible = false;
				if (bFadedIn) {
					_parent.gotoAndPlay("fadeOut");
					bFadedIn = false;
				}
				skse.CloseMenu("Loading Menu");
			}*/
		}
		return bHandledInput;
	}

	function SetLevelProgress(afCurrentLevel, afLevelProgress)
	{
		LevelMeterRect.LevelNumberLabel.SetText(afCurrentLevel);
		LevelMeter_mc.SetPercent(afLevelProgress);
	}
	
	function SetButtonArt(abGamepad){
		if (abGamepad){
			PrevButton.gotoAndStop(274);
			NextButton.gotoAndStop(275);
		} else {
			PrevButton.gotoAndStop(16);
			NextButton.gotoAndStop(19);
		}
	}

	function SetLoadingText(astrText:String):Void
	{
		if (astrText != undefined)
		{
			LoadingText.SetText(astrText);
			LoadingTextFader._visible = true;
			return;
		}
		LoadingTextFader._visible = false;
	}

	function refreshLoadingText():Void
	{
		GameDelegate.call("RequestLoadingText",[],this,"SetLoadingText");
		//LoadingTextFader.gotoAndPlay("fadeIn");
	}

	function SetLocationText(locText:String):Void
	{
		if (locText != "")
		{
			LocationText.SetText(locText);
			LocationFader._visible = true;
			
			LocationBackground._x = - 65 - (locText.length * 7);
			return;
		}
		LocationFader._visible = false;
	}

	function refreshLocationText():Void
	{
		skse.SendModEvent("RequestLocationText");
	}

	function FadeInMenu():Void
	{
		if (bFadedIn)
		{
			return;
		}
		MessagesMemory = [];
		memoryIndex = 0;
		ContinueButtonFader._visible = false;
		PrevButton._visible = true;
		NextButton._visible = true;
		//LocationBackground._x = - 33;
		GameDelegate.call("RequestPlayerInfo",[],this,"SetLevelProgress");
		refreshLocationText();
		refreshLoadingText();
		skse.SendModEvent("RequestUseGamepad");
		_parent.gotoAndPlay("fadeIn");
		bFadedIn = true;
	}

	function FadeOutMenu(): Void
	{
		//ContinueButtonFader._visible = true;
		bFadedIn = false;
		if (bFadedIn) {
			_parent.gotoAndPlay("fadeOut");
			bFadedIn = false;
		}
	}
}