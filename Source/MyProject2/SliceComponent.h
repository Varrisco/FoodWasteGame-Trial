// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlicingGameMode.h" //Talvez não seja necessário
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SliceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API USliceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USliceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
