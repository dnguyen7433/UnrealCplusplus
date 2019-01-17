// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h "
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();
	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnCloseRequest;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	// UPROPERTY is a macro which do cut-and-paste a specific specifier. 
	

	UPROPERTY(EditAnywhere) 
	ATriggerVolume* PressurePlate = nullptr; 

	UPROPERTY(EditAnyWhere)
	float TriggerMass = 30.0f;

	// The Owning door 
	AActor* Owner; 

	// Return the total mass on the pressure plate that allows the door to open
	float GetTotalMassOfActorOnPressurePlate(); 
};
