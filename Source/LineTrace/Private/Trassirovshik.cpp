
#include "Trassirovshik.h"
#include <ocidl.h>
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include <vector>

ATrassirovshik::ATrassirovshik()
{
	PrimaryActorTick.bCanEverTick = true;
	TrassirovshikMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TrassirovshikMesh"));
	TrassirovshikMesh->SetupAttachment(GetRootComponent());
}


void ATrassirovshik::BeginPlay()
{
	Super::BeginPlay();
}


void ATrassirovshik::Interact()
{
	
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 5000.f;
	TArray<FHitResult> OutHitsForward;
	TArray<FHitResult> OutHitsBackward;
	TArray<FVector> ImpactPointForwards;
	TArray<FVector> ImpactPointBackwards;
	TArray<float> LengthArray;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

//forward trace
	if (GetWorld()->LineTraceMultiByObjectType(OutHitsForward, Start, End, ECC_WorldStatic, Params))
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);
		for (const FHitResult& HitResult : OutHitsForward)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				FVector ImpactPointForward = HitResult.ImpactPoint;
				ImpactPointForwards.Add(ImpactPointForward);
			}
		}
	}
	
//backward trace
	if (GetWorld()->LineTraceMultiByObjectType(OutHitsBackward, End, Start, ECC_WorldStatic, Params))
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);
		for (const FHitResult& HitResult : OutHitsBackward)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				FVector ImpactPointBackward = HitResult.ImpactPoint;
				ImpactPointBackwards.Add(ImpactPointBackward);
			}
		}
	}

	//vector length
	for (int32 a = 0; a < ImpactPointForwards.Num(); ++a)
	{
		// Получаем пару векторов
		const FVector& StartVector = ImpactPointForwards[a];
		const FVector& EndVector = ImpactPointBackwards[ImpactPointBackwards.Num() - 1 - a];

		// Вычисляем длину вектора между началом и концом
		float Length = (EndVector - StartVector).Size();
		LengthArray.Add(Length);
	}

	// Вывод элементов матрицы
	for (int32 Index = 0; Index < LengthArray.Num(); ++Index)
	{
		UE_LOG(LogTemp, Warning, TEXT("Толщина %d ого объекта: %f"), Index+1, LengthArray[Index]);
	}
	
}

void ATrassirovshik::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrassirovshik::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("Interact"), IE_Pressed, this, &ATrassirovshik::Interact);
}

