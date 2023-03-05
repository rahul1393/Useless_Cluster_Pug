// Fill out your copyright notice in the Description page of Project Settings.


#include "IceTile.h"

UIceTile::UIceTile()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UIceTile::BeginPlay()
{
	Super::BeginPlay();	
}

void UIceTile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIceTile::KillIceBlock()
{
	if (MeshComponent != nullptr)
	{
		MeshComponent->SetVisibility(false, true);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}