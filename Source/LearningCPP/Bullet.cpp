// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
ABullet::ABullet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	RootComponent = ProxSphere;
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::Prox);
	Damage = 1;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		// не сталкиваемся ни с чем другим
		// кроме актора root component
		return;
	}
	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);
	Destroy();
}