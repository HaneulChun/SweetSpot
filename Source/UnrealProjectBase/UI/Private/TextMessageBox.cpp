// All Rights Reserved by SweetSpot 2025-2026.


#include "UnrealProjectBase/UI/Public/TextMessageBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

UATextMessageBox::UATextMessageBox() : WBP_MessageBox_Container(nullptr), Text_MessageBox(nullptr)
{
}

void UATextMessageBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (!WBP_MessageBox_Container)
	{
	}
}

void UATextMessageBox::NativeTick(float DeltaTime)
{
	Super::NativeTick(DeltaTime);

	if (Text_MessageBox)
	{
		std::string const PushedPlayerMessage = "<Message>";
		FString MessageBox_Text = "PushedPlayerMessage";
		Text_MessageBox->SetText(FText::FromString(MessageBox_Text));
	}
}