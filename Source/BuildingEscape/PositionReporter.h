// Fill out your copyright notice in the Description page of Project Settings. // Unreal -> Setting -> ProjectSetting -> Project Description

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PositionReporter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) // Telling the unreal header tool how to work with the class
class BUILDINGESCAPE_API UPositionReporter : public UActorComponent // Inherited from UActorComponent
{
	GENERATED_BODY() // Tell Unreal to do some magic

public:	
	// Sets default values for this component's properties
	UPositionReporter(); // Constructor

protected:
	// Called when the game starts
	virtual void BeginPlay() override; // VIRTUAL means that we are not gonna say how it works here
										// we will responsible for it somewhere else

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
