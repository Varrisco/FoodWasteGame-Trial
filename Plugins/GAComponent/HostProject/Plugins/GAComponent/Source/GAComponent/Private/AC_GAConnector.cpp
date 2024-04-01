// German Todua. 2024. All Rights Reserved.


#include "AC_GAConnector.h"

// Sets default values for this component's properties
UAC_GAConnector::UAC_GAConnector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = false;

	Http = &FHttpModule::Get();

}


// Called when the game starts. Generate IDs
void UAC_GAConnector::BeginPlay()
{
	Super::BeginPlay();
	GenerateIDS();

}

void UAC_GAConnector::GenerateIDS()
{

	//Generate ID Part

	IDS1 = FMath::RandRange(10000, 99999);
	IDS2 = FMath::RandRange(10000, 99999);
	IDS3 = FMath::RandRange(10000, 99999);
	IDS4 = FMath::RandRange(10000, 99999);

	//Generate SID

	SID1 = FMath::RandRange(10000, 99999);
	SID2 = FMath::RandRange(10000, 99999);

}


//Called every frame
void UAC_GAConnector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}


void UAC_GAConnector::SendEventToGoogleAnalytics(UPARAM(ref) FString EventName, TMap <FString, FString> AdditionalInfo)
{
	//Get Info About Character
	FString ActorCoordinates = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().ToString();


	//Get Play Time
	int realtimeSeconds = GetWorld()->GetRealTimeSeconds();
	int PlayedMS = realtimeSeconds * 1000;

	//Some Math for Google Time Standarts for event to time
	FString EngamentAsString = FString::FromInt(PlayedMS);
	FString PlayesAsString = FString::FromInt(realtimeSeconds);

	FString PlayTime = FString::Printf(TEXT("&_et=%s"), *EngamentAsString);
	FString TimePlayed = FString::Printf(TEXT("&ep.time_to_event=%s"), *PlayesAsString);


	//Base String Constructor

	FString URLPart1 = ("https://www.google-analytics.com/g/collect"); //Base URL

	//Generating or use premade ClientID
	FString URLCID;
	URLCID = FString::Printf(TEXT("?cid=%i%i.%i%i"), IDS1, IDS2, IDS3, IDS4);


	//Preset Strings
	FString URLPart2 = ("&_p=pfJ.Aev&seg=1");

	//Session ID
	FString URLSID = FString::Printf(TEXT("&sid=%i%i"), SID1, SID2);

	//Additional Preset String
	FString URLPart3 = FString::Printf(TEXT("&ul=en&v=2&_z=ccd.v9b"));

	//Base URL Construction
	FString BaseURL = FString::Printf(TEXT("%s%s%s%s%s&tid=%s%s"), *URLPart1, *URLCID, *PlayTime, *URLPart2, *URLSID, *GoogleMeasurementID, *URLPart3);


	//For Debugging (DELETE AFTER)
	UE_LOG(LogTemp, Display, TEXT("connection via URL %s"), *URLCID, *BaseURL);


	//SetupParameters - EventName From Inout
	FString EventPointer = FString::Printf(TEXT("&en=%s"), *EventName);


	//Get Data From Map and create arrays

	TArray<FString> AdditionalInfoKeys;
	TArray<FString> AdditionalInfoValues;

	AdditionalInfo.GenerateKeyArray(AdditionalInfoKeys);
	AdditionalInfo.GenerateValueArray(AdditionalInfoValues);

	int SizeParameterArray = FMath::Min(AdditionalInfoKeys.Num(), AdditionalInfoValues.Num()); // get minimal elems

	FString EventData;
	for (int i = 0; i < SizeParameterArray; ++i)
	{
		EventData += FString::Printf(TEXT("&ep.%s=%s"), *AdditionalInfoKeys[i], *AdditionalInfoValues[i]); // loop with index
	}


	//here should be added xaxis yaxis zaxis from above
	FString URL = FString::Printf(TEXT("%s%s%s&ep.event_coordinate=%s%s"), *BaseURL, *EventPointer, *TimePlayed, *ActorCoordinates, *EventData);

	//Make URL fit for POST -- Remove Spacers
	URL.RemoveSpacesInline();

	//Creating the request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>Request = Http->CreateRequest();

	//Bind response function to request
	Request->OnProcessRequestComplete().BindUObject(this, &UAC_GAConnector::OnGetTimeResponse);

	//Setting the URL -- What kind and where request is sended
	Request->SetURL(URL);

	//Set Verb
	Request->SetVerb("GET");


	//Info for Server to know what kind of application connects
	Request->SetHeader("User-Agent", "X - UnrealEngine - Agent");

	//Let request know what response we are expecting
	Request->SetHeader("Content-Type", "application/json");

	//Sending the request
	Request->ProcessRequest();

}


void UAC_GAConnector::SendSimpleEventToGoogleAnalytics(UPARAM(ref) FString EventName)
{
	//Get Info About Character
	FString ActorCoordinates = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().ToString();


	//Get Play Time
	int realtimeSeconds = GetWorld()->GetRealTimeSeconds();
	int PlayedMS = realtimeSeconds * 1000;

	//Some Math for Google Time Standarts for event to time
	FString EngamentAsString = FString::FromInt(PlayedMS);
	FString PlayesAsString = FString::FromInt(realtimeSeconds);

	FString PlayTime = FString::Printf(TEXT("&_et=%s"), *EngamentAsString);
	FString TimePlayed = FString::Printf(TEXT("&ep.time_to_event=%s"), *PlayesAsString);


	//Base String Constructor

	FString URLPart1 = ("https://www.google-analytics.com/g/collect"); //Base URL

	//Generating or use premade ClientID
	FString URLCID;
	URLCID = FString::Printf(TEXT("?cid=%i%i.%i%i"), IDS1, IDS2, IDS3, IDS4);


	//Preset Strings
	FString URLPart2 = ("&_p=pfJ.Aev&seg=1");

	//Session ID
	FString URLSID = FString::Printf(TEXT("&sid=%i%i"), SID1, SID2);

	//Additional Preset String
	FString URLPart3 = FString::Printf(TEXT("&ul=en&v=2&_z=ccd.v9b"));

	//Base URL Construction
	FString BaseURL = FString::Printf(TEXT("%s%s%s%s%s&tid=%s%s"), *URLPart1, *URLCID, *PlayTime, *URLPart2, *URLSID, *GoogleMeasurementID, *URLPart3);


	//For Debugging (DELETE AFTER)
	UE_LOG(LogTemp, Display, TEXT("connection via URL %s"), *URLCID, *BaseURL);


	//SetupParameters - EventName From Input
	FString EventPointer = FString::Printf(TEXT("&en=%s"), *EventName);

	//here should be added xaxis yaxis zaxis from above
	FString URL = FString::Printf(TEXT("%s%s%s&ep.event_coordinate=%s"), *BaseURL, *EventPointer, *TimePlayed, *ActorCoordinates);

	//Make URL fit for POST -- Remove Spacers
	URL.RemoveSpacesInline();

	//Creating the request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>Request = Http->CreateRequest();

	//Bind response function to request
	Request->OnProcessRequestComplete().BindUObject(this, &UAC_GAConnector::OnGetTimeResponse);

	//Setting the URL -- What kind and where request is sended
	Request->SetURL(URL);

	//Set Verb
	Request->SetVerb("GET");


	//Info for Server to know what kind of application connects
	Request->SetHeader("User-Agent", "X - UnrealEngine - Agent");

	//Let request know what response we are expecting
	Request->SetHeader("Content-Type", "application/json");

	//Sending the request
	Request->ProcessRequest();

}

//Build up for updates
void UAC_GAConnector::OnGetTimeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{

}