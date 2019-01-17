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
// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Poll the trigger volume
	
	if (GetTotalMassOfActorOnPressurePlate() > TriggerMass) {
		// If that actor is in the volume
		OnOpenRequest.Broadcast();
	}
	else {
	OnCloseRequest.Broadcast();
	}
	// Check if the door close after opening for 2 seconds
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