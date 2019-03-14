// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngel, 0.f));
}

void UOpenDoor::CloseDoor()
{
	FRotator OpenDoor = FRotator(0.f, -90.f, 0.f);
	Owner->SetActorRotation(OpenDoor);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > 35.f) // TODO make into parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();

	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	
	TArray<AActor*> OverlappingActors;
	//find all overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	//iterate through actors to calculate mass
	for (auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate."), *Actor->GetName())
	}
	return TotalMass;
}