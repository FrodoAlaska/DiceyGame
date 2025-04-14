#include "app.h"
#include "entities/dice.h"

#include <nikola/nikola.h>

/// ----------------------------------------------------------------------
/// App 
struct nikola::App {
  nikola::Window* window; 
  nikola::Camera camera;
  nikola::RenderQueue render_queue;
  
  nikola::u16 resource_group;
  nikola::ResourceID skybox_id, material_id;
  nikola::DynamicArray<nikola::ResourceID> shader_contexts;
  
  nikola::i32 effect_index = 0;
  Dice dices[DICES_MAX]; 
};
/// App 
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// Callbacks 

static void geometry_pass(const nikola::RenderPass* prev, nikola::RenderPass* pass, void* user_data) {
  nikola::App* app = (nikola::App*)user_data;

  // Render everything
  nikola::render_queue_flush(app->render_queue);
}

static void post_process_pass(const nikola::RenderPass* prev, nikola::RenderPass* pass, void* user_data) {
  nikola::App* app = (nikola::App*)user_data;

  // Set the shader
  nikola::shader_context_set_uniform(pass->shader_context_id, "u_effect_index", app->effect_index);

  pass->frame_desc.attachments[0]    = prev->frame_desc.attachments[0];
  pass->frame_desc.attachments_count = 1;
}

/// Callbacks 
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// Private functions

static void init_resources(nikola::App* app) {
  // Resource group init
  nikola::FilePath current_path = nikola::filesystem_current_path();
  nikola::FilePath res_path = nikola::filepath_append(current_path, "res");
  app->resource_group = nikola::resources_create_group("game_res", res_path); 

  // Shaders init
  nikola::ResourceID default_shader      = nikola::resources_push_shader(app->resource_group, "shaders/default_shader.nbrshader");
  nikola::ResourceID cubemap_shader      = nikola::resources_push_shader(app->resource_group, "shaders/cubemap_shader.nbrshader");
  nikola::ResourceID geo_pass_shader     = nikola::resources_push_shader(app->resource_group, "shaders/geo_pass.nbrshader");
  nikola::ResourceID post_process_shader = nikola::resources_push_shader(app->resource_group, "shaders/post_process.nbrshader");

  // Cubemaps init
  nikola::resources_push_cubemap(app->resource_group, "cubemaps/desert_cubemap.nbrcubemap");

  // Models init
  nikola::resources_push_model(app->resource_group, "models/dice.nbrmodel");
  
  // Shader contexts init
  app->shader_contexts.push_back(nikola::resources_push_shader_context(app->resource_group, default_shader));
  app->shader_contexts.push_back(nikola::resources_push_shader_context(app->resource_group, cubemap_shader));
  app->shader_contexts.push_back(nikola::resources_push_shader_context(app->resource_group, geo_pass_shader));
  app->shader_contexts.push_back(nikola::resources_push_shader_context(app->resource_group, post_process_shader));

  // Skybox init
  app->skybox_id = nikola::resources_push_skybox(app->resource_group, nikola::resources_get_id(app->resource_group, "desert_cubemap")); 

  // Material init
  app->material_id = nikola::resources_push_material(app->resource_group); 
}

static void init_passes(nikola::App* app) {
  nikola::i32 width, height; 
  nikola::window_get_size(app->window, &width, &height);
  
  // Geometry pass
  nikola::RenderPassDesc render_pass = {
    .frame_size        = nikola::Vec2(width, height), 
    .clear_color       = nikola::Vec4(0.1f, 0.1f, 0.1f, 1.0f),
    .clear_flags       = (nikola::GFX_CLEAR_FLAGS_COLOR_BUFFER | nikola::GFX_CLEAR_FLAGS_DEPTH_BUFFER),
    .shader_context_id = app->shader_contexts[2],
  };
  render_pass.targets.push_back(nikola::GFX_TEXTURE_FORMAT_RGBA8);
  nikola::renderer_push_pass(render_pass, geometry_pass, app);

  // Post-process pass
  render_pass.clear_flags       = nikola::GFX_CLEAR_FLAGS_COLOR_BUFFER; 
  render_pass.shader_context_id = app->shader_contexts[3];
  nikola::renderer_push_pass(render_pass, post_process_pass, app);
}

static void init_render_queue(nikola::App* app) {
  // Skybox command
  nikola::RenderCommand rnd_cmd;
  rnd_cmd.render_type       = nikola::RENDERABLE_TYPE_SKYBOX; 
  rnd_cmd.renderable_id     = app->skybox_id; 
  rnd_cmd.material_id       = app->material_id; 
  rnd_cmd.shader_context_id = app->shader_contexts[1]; 
  nikola::render_queue_push(app->render_queue, rnd_cmd);

  // Dice command
  rnd_cmd.render_type       = nikola::RENDERABLE_TYPE_MODEL; 
  rnd_cmd.material_id       = app->material_id; 
  rnd_cmd.shader_context_id = app->shader_contexts[0]; 
  for(nikola::sizei i = 0; i < DICES_MAX; i++) {
    if(!app->dices[i].is_active) {
      continue;
    }

    rnd_cmd.renderable_id = app->dices[i].skin_id; 
    rnd_cmd.transform     = &app->dices[i].transform;
    nikola::render_queue_push(app->render_queue, rnd_cmd);
  }
}

static void init_dices(nikola::App* app) {
  dice_create(&app->dices[0], nikola::Vec3(10.0f, 0.0f, 10.0f), nikola::resources_get_id(app->resource_group, "dice"));
}

/// Private functions
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// App functions 

nikola::App* app_init(const nikola::Args& args, nikola::Window* window) {
  // App init
  nikola::App* app = new nikola::App{};

  // Window init 
  app->window = window; 

  // Camera init 
  nikola::f32 aspect_ratio = nikola::window_get_aspect_ratio(window);
  nikola::camera_create(&app->camera, aspect_ratio, nikola::Vec3(10.0f, 0.0f, 10.0f), nikola::Vec3(-3.0f, 0.0f, 0.0f));

  // Resources init
  init_resources(app);

  // Passes init
  init_passes(app);
  
  // Dices init
  init_dices(app);

  // Render queue init
  init_render_queue(app);

  return app;
}

void app_shutdown(nikola::App* app) {
  nikola::resources_destroy_group(app->resource_group);
  delete app;
}

void app_update(nikola::App* app, const nikola::f64 delta_time) {
  if(nikola::input_key_down(nikola::KEY_ESCAPE)) {
    nikola::event_dispatch(nikola::Event{.type = nikola::EVENT_APP_QUIT});
    return;
  }

  nikola::camera_update(app->camera);
}

void app_render(nikola::App* app) {
  nikola::renderer_begin(app->camera);

  nikola::renderer_apply_passes();
  nikola::renderer_end();
}

/// App functions 
/// ----------------------------------------------------------------------
