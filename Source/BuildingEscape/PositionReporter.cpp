// Fill out your copyright notice in the Description page of Project Settings.
#include "PositionReporter.h"
#include "Gameframework/Actor.h"




// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // true means this bit of code will be run every single frame

}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay(); // Super means that doing whatever happened up the inheritance tree
						// that is, whatever happened up in the UActorComponent do that first, leave the engine to do that
	FString ObjectName = GetOwner()->GetName(); 
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is in %s"),*ObjectName,*ObjectPos);// *  here is NOT dereferencing the pointer to an memory address, 
												// but * is an overloaded operator that macro in Unreal used.

	// UE_LOG is a macro or Unreal header tool directive
	// LogTemp is the log (record) it is going to be 
	// Warning is to make the log come out at a particular color
	// ...
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

