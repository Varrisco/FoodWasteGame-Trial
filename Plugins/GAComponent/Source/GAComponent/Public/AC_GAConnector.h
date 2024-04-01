// German Todua. 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HttpModule.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "AC_GAConnector.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GACOMPONENT_API UAC_GAConnector : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_GAConnector();

	//Used to send HTTP Request
	UFUNCTION(BlueprintCallable, Category = "Events")
		void SendEventToGoogleAnalytics(UPARAM() FString EventName, TMap<FString, FString> AdditionalData);

	//Used to send Simple Event Request
	UFUNCTION(BlueprintCallable, Category = "Events")
		void SendSimpleEventToGoogleAnalytics(UPARAM() FString EventName);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Required Setup Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Settings")
		FString GoogleMeasurementID;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void GenerateIDS();


	//Handle the HttpRequest Response (not used rn)
	void OnGetTimeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);


private:

	int IDS1;
	int IDS2;
	int IDS3;
	int IDS4;
	int SID1;
	int SID2;

	//UPROPERTY()
	//FString ActorLocation;

	FHttpModule* Http;

}
;