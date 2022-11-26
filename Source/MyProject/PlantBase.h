// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PlantBase.generated.h"

UCLASS()
class MYPROJECT_API APlantBase : public AActor
{
	GENERATED_BODY()

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;

	const int32 step = 25;

	UFUNCTION(BlueprintCallable)
	void CreateOptimizedMesh();
public:	
	// Sets default values for this actor's properties
	APlantBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* ProcMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector2D PlantFieldSize = FVector2D(1000,200);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void AddQuad(int x, int y);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
