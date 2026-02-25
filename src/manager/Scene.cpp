//
// Created by Curry on 2026-02-25.
//

#include  "Scene.h"
#include  "AssetManager.h"

Scene::Scene(const char *sceneName, const char *mapPath, int windowWidth, int windowHeight): name(sceneName) {


    //load map
    world.getMap().load(mapPath,TextureManager::load("../asset/tileset.png"));
    for (auto& collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x,collider.rect.y),0.0f,1.0f);
        auto& c = e.addComponent<Collider>("wall");

        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        SDL_Texture* tex = TextureManager::load("../asset/tileset.png");
        SDL_FRect colSrc {0,32,32,32};
        SDL_FRect colDst {c.rect.x,c.rect.y,c.rect.w,c.rect.h};
        e.addComponent<Sprite>(tex,colSrc,colDst);
    }


    //add coins
    for (auto& coin : world.getMap().coins) {
        auto& item = world.createEntity();
        item.addComponent<Transform>(Vector2D(coin.rect.x,coin.rect.y),0.0f,1.0f);
        auto& c = item.addComponent<Collider>("item");

        c.rect.x = coin.rect.x;
        c.rect.y = coin.rect.y;

        SDL_Texture* tex = TextureManager::load("../asset/coin.png");
        SDL_FRect colSrc {0,0,32,32};
        SDL_FRect colDst {c.rect.x,c.rect.y,32,32};
        item.addComponent<Sprite>(tex,colSrc,colDst);
    }
    // auto& item(world.createEntity());
    // auto& itemTransform = item.addComponent<Transform>(Vector2D(100,200), 0.0f,1.0f);
    //
    // SDL_Texture*  itemTex = TextureManager::load("../asset/coin.png");
    // SDL_FRect itemSrc{0,0,32,32};
    //
    // SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y,32,32};
    // item.addComponent<Sprite>(itemTex,itemSrc,itemDest);
    //
    // auto& itemCollider = item.addComponent<Collider>("item");
    // itemCollider.rect.w = itemDest.w;
    // itemCollider.rect.h = itemDest.h;

    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, static_cast<float>(world.getMap().width * 32), static_cast<float>(world.getMap().height * 32));


    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0,0),1.0f);
    player.addComponent<Velocity>(Vector2D(0,0), 120.0f);

    Animation anim = AssetManager::getAnimation("player");
    player.addComponent<Animation>(anim);

    SDL_Texture* tex = TextureManager::load("../asset/animations/fox_anim.png");
    // SDL_FRect playerSrc {0,0,32,44};
    SDL_FRect playerSrc = anim.clips[anim.currentClip].frameIndicies[0];
    SDL_FRect playerDst {playerTransform.position.x,playerTransform.position.y,64,64};
    player.addComponent<Sprite>(tex,playerSrc,playerDst);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    player.addComponent<PlayerTag>();


    auto& spawner(world.createEntity());
    Transform t = spawner.addComponent<Transform>(Vector2D(windowWidth/2,windowHeight - 5),0.0f,1.0f);
    spawner.addComponent<TimedSpawner>(2.0f,[this,t] {

        //create projectiles
        auto& e(world.createDeferredEntity());
        e.addComponent<Transform>(Vector2D(t.position.x,t.position.y),0.0f,1.0f);
        e.addComponent<Velocity>(Vector2D(0,-1),100.0f);

        Animation anim = AssetManager::getAnimation("enemy");
        e.addComponent<Animation>(anim);

        SDL_Texture* tex = TextureManager::load("../asset/animations/bird_anim.png");
        SDL_FRect src = {0,0,32,32};
        SDL_FRect dst {t.position.x,t.position.y,32,32};
        e.addComponent<Sprite>(tex,src,dst);

        Collider c = e.addComponent<Collider>("projectile");
        c.rect.w = dst.w;
        c.rect.h = dst.h;

        e.addComponent<ProjectileTag>();

    });


    //add scene state
    auto &state(world.createEntity());
    state.addComponent<SceneState>();
}