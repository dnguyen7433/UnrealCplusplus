// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "UObject/UObjectGlobals.h"
#include "Components/PrimitiveComponent.h"
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
//  Looking for the physical handle
void UGrabber::FindAttachedPhysicalHandle()
{
	PhysicalHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicalHandle == nullptr){
		// Reporting to the reader if no handle is found
		UE_LOG(LogTemp, Error, TEXT("The handle of %s is not found! Please attach a physics handle to %s."), *(GetOwner()->GetName()));
	}
}
// Looking for the input component
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

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Press to Grab"))
		/// Line trace and see if we reach any actors with physics body collision set
	auto Hit = ReturnFirstPhysicalBodyInReach();
	auto ComponentToGrab = Hit.GetComponent();
	auto ActorHit = Hit.GetActor();
	/// If we hit something, then attach the physics handle
	if (ActorHit != nullptr)
	{
		PhysicalHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // Allow Rotation
		);

	}
}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab is released"))
		// Release the object.
		PhysicalHandle->ReleaseComponent();

}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Look for the physics handle
	PhysicalHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// When the physics handle is attached, then grab the object and move the object within the LineTraceEnd
	if (PhysicalHandle) {
		if (PhysicalHandle->GrabbedComponent) {
			PhysicalHandle->SetTargetLocation(RayCastingToReachTheObject());
		}
	}
}


// Report if any physical body is hit
const FHitResult UGrabber::ReturnFirstPhysicalBodyInReach()
{
	// Getting the hit result
	FHitResult Hit = HitResult(RayCastingToReachTheObject());
	// Getting the name of the object hit
	HitObject = Hit.GetActor();
	if (HitObject) {
		UE_LOG(LogTemp, Warning, TEXT("%s is hit!!!"), *(HitObject->GetName()))
	}
	return Hit;
}
// Calculating the LineTraceEnd based on the player's rotation and location
FVector UGrabber::RayCastingToReachTheObject()
{
	// Get the player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	// Draw the line trace end
	FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);
	return LineTraceEnd;
}
// Returning the hit result if any object is within the player's LineTraceEnd distance
FHitResult UGrabber::HitResult(FVector LineTraceEnd)
{
	///Set up query parameters
	FCollisionQueryParams TracePram(FName(TEXT(" ")), false, GetOwner());
	///Ray cast (AKA Line trace) to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
	OUT HitResult,
	OUT PlayerLocation,
	OUT LineTraceEnd,
	OUT FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	OUT TracePram);
	return HitResult;
}


