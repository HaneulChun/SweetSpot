// All Rights Reserved by SweetSpot 2025-2026.


#include "UnrealProjectBase/UI/Public/TextMessageBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

ATextMessageBox::ATextMessageBox() : WBP_MessageBox_Container(nullptr), Text_MessageBox(nullptr)
{
}

void ATextMessageBox::BeginPlay()
{
	Super::BeginPlay();

	if (!WBP_MessageBox_Container)
	{
	}

	MessageToDisplay = TEXT("");
}

void ATextMessageBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Text_MessageBox)
	{
		Text_MessageBox->SetText(FText::FromString(MessageToDisplay));
	}
}