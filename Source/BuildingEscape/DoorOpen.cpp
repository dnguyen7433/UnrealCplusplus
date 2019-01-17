// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/Array.h"



#define OUT
// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate of %s is missing!!!"), *(GetOwner()->GetName()))
	}
}

void UDoorOpen::OpenTheDoor()
{
	
	// Setting the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	
}
void UDoorOpen::CloseTheDoor()
{
	
	// Setting the door rotation
	Owner->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Poll the trigger volume
	
	if (GetTotalMassOfActorOnPressurePlate() > 20.0f) {
	// If that actor is in the volume
	LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	OpenTheDoor();
	}
	// Check if the door close after opening for 2 seconds
	
	if ((GetWorld() ->GetTimeSeconds ()) >= (LastDoorOpenTime + DoorCloseDelay)) {
	CloseTheDoor();
	}
}

float UDoorOpen:: GetTotalMassOfActorOnPressurePlate() {
	float TotalMass = 0.f;
	if (PressurePlate == nullptr) {
		
		return TotalMass;
	}


	// Find all the overlapping actors

	TArray<AActor*> OverlappingActors;

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	
		for (const auto& Actor : OverlappingActors)

		{
			if (Actor) {
				TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

				UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
			}
		}
	
	return TotalMass;
}