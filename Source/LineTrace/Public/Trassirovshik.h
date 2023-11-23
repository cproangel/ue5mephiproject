// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Trassirovshik.generated.h"

class USkeletalMeshComponent;

UCLASS()
class LINETRACE_API ATrassirovshik : public APawn
{
	GENERATED_BODY()

public:
	ATrassirovshik();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void Interact();

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* TrassirovshikMesh;
};
