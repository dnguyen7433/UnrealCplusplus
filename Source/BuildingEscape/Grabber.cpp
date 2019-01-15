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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindAttachedPhysicalHandle();
	FindInputComponent();
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Press to Grab"))
		/// Line trace and see if we reach any actors with physics body collision set

		/// If we hit something, then attach the physics handle

		// TODO attach physics handle

}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab is released"))
}
//  Looking for the physical handle
void UGrabber::FindAttachedPhysicalHandle()
{
	
	PhysicalHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicalHandle) {
		// Handle is found
	}
	else {
		// Reporting to the reader if no handle is found
		UE_LOG(LogTemp, Error, TEXT("The handle of %s is not found!!!"), *(GetOwner()->GetName()));
	}
}
/// Looking for the input component
void UGrabber::FindInputComponent()
{
	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		// Input Component is found
		UE_LOG(LogTemp, Error, TEXT("InputComponent of %s is found!!!"), *(GetOwner()->GetName()))
			// Assing a key for the grabbing action
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // Bind an action to the InputComponent (this). That is,
																					// after pressing the key for "Grab", then performing 
																					// the action defined in Grab() function
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent of %s is not found!!!"), *(GetOwner()->GetName()))
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ReturnFirstPhysicalBodyInReach();
	/// If the physics handle is attached

		// TODO move the object every single frame

	
}
// Report if any physical body is hit
const FHitResult UGrabber::ReturnFirstPhysicalBodyInReach()
{
	// Get the player's viewpoint
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	// Report about the player's viewpoint in the output log
	//UE_LOG(LogTemp, Warning, TEXT("Rotation(%s) and Location(%s)"), *Rotation.ToString(), *Location.ToString())
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
	return HitResult;
}