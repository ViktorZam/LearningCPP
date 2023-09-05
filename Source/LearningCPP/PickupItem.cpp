// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

// Sets default values
APickupItem::APickupItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Name = "UNKNOWN ITEM"; // “НЕИЗВЕСТНЫЙ ПРЕДМЕТ”
		Quantity = 0;
	// Задаём объект Unreal
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	// делаем корневым объектом Mesh
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	// Пишем код для запуска APickupItem::Prox(), когда эта
	// сфера близости объекта пересекается с другим актором.
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this,&APickupItem::Prox);
	ProxSphere->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // очень важно!
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// если актор, с которым произошло пересечение, НЕ является игроком,
// вы просто должны вернуться
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	// Получаем ссылку на аватар игрока, чтобы дать ему предмет
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// Позволяем игроку подбирать предмет
	// Обратите на ключевое слово this!
	// Это то, как _this_ Pickup может ссылаться на само себя.
	avatar->Pickup(this);
	// Получаем ссылку на контроллер
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	// Получаем ссылку на HUD из контроллера
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->addMessage(Message(FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, 5.f, FColor::White, Icon));
	Destroy();
}