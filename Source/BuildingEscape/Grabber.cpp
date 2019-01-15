// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "UObject/UObjectGlobals.h"
#include "CollisionQueryParams.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	
	

	//Ray cast to reach distance
	//See what we hit
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Get the player's viewpoint
	FVector Location ;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	// Report about the player's viewpoint in the output log
	UE_LOG(LogTemp, Warning, TEXT("Rotation(%s) and Location(%s)"), *Rotation.ToString(), *Location.ToString())
	///Draw a red trace in the world to visualize
	FVector LineTraceEnd = Location + (Rotation.Vector() * Reach);
	FColor Color(1, 0, 0);
	DrawDebugLine(OUT GetWorld(), 
		Location, 
		LineTraceEnd, 
		Color, 
		false, 0, 0, 10.f);
	///Set up query parameters
	FCollisionQueryParams TracePram(FName(TEXT(" ")), false, GetOwner());
	///Ray cast (AKA Line trace) to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TracePram);
	// See what we hit
	HitObject = HitResult.GetActor();

	if (HitObject) {
		UE_LOG(LogTemp, Warning, TEXT("%s is hit!!!"), *(HitObject->GetName()))
	}
}

