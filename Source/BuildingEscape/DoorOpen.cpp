// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "Engine/EngineTypes.h"



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
	// Explaination: In order to find the default pawn, we go to the world, we go top-down, 
	// we look for player controller (MIND)
	// and then we go and get the Pawn (BODY)
	ActorOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn(); // Because A pawn IS A Actor
																		//; therefore, ActorOpenDoor of AActor* can be assigned as APawn*
	
}

void UDoorOpen::OpenTheDoor()
{
	// Finding the owning actor
	AActor* Owner = GetOwner();

	// Creating a rotator
	FRotator NewRotation(0.0f, -0.000292, 0.0f);
	// Setting the door rotation
	Owner->SetActorRotation(NewRotation);
	// ...
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Poll the trigger volume
	if ( PressurePlate&& PressurePlate->IsOverlappingActor(ActorOpenDoor)) {
	// If that actor is in the volume
	OpenTheDoor();
	}
}

