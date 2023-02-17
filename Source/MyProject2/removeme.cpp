#include "removeme.h"

// Sets default values
Aremoveme::Aremoveme()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aremoveme::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aremoveme::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void Aremoveme::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
