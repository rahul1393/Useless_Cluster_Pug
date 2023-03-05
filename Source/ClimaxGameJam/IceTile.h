// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IceTile.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLIMAXGAMEJAM_API UIceTile : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIceTile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
		void KillIceBlock();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsLivingBlock = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsBearBlock = false;
		
};
