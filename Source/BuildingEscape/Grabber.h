// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Controller.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	
	float Reach = 100.f; // Multiply to reach the distance
	AActor* HitObject;
	UPhysicsHandleComponent* PhysicalHandle = nullptr;  // Declare Physics Handle to move objects
	UInputComponent* InputComponent = nullptr;
	FVector PlayerLocation;
	FRotator PlayerRotation;

	// R-cast and grab an object
	void Grab();

	// Called when grab is released
	void Release();

	// Find the (assumed) attached physical handler
	void FindAttachedPhysicalHandle();

	// Find the (assumed) attached input component
	void FindInputComponent();

	// Return hit for first physics body is hit
	const FHitResult ReturnFirstPhysicalBodyInReach();

	// Set up the Line Tracing to reach the object 
	FVector RayCastingToReachTheObject();

	// Getting the hit result when the grabber hit the object
	FHitResult HitResult(FVector);

};
