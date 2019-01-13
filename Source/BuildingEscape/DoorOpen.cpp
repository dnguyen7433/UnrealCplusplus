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
	Owner = GetOwner();
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
	if ( PressurePlate&& PressurePlate->IsOverlappingActor(ActorOpenDoor)) {
	// If that actor is in the volume
	LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	OpenTheDoor();
	}
	// Check if the door close after opening for 2 seconds
	
	if ((GetWorld() ->GetTimeSeconds ()) >= (LastDoorOpenTime + DoorCloseDelay)) {
	CloseTheDoor();
	}
}

