#include "e_camera.h"

gearworks::elem_camera::cam_properties_struct::cam_properties_struct() :
	position(vec3(0, 0, -100)),
	yaw(-90.0f), pitch(0.0f), roll(0.0f),
	target_position(vec3(0)),
	local_forward_direction(vec3(0, 0, -1)),
	local_up_direction(vec3(0, 1, 0)),
	forward(vec3(0, 0, 0)),
	back(vec3(0, 0, 0)),
	left(vec3(0, 0, 0)),
	right(vec3(0, 0, 0)),
	fov(45.0f)
{}

void gearworks::elem_camera::update_camera(renderer *ren) {
	// Update the forward local direction
	properties.local_forward_direction = glm::normalize(properties.position - properties.target_position);

	// Update the front value
	vec3 dir = vec3(0);
	dir.x = cos(glm::radians(properties.yaw)) * cos(glm::radians(properties.pitch));
	dir.y = sin(glm::radians(properties.pitch));
	dir.z = sin(glm::radians(properties.yaw)) * cos(glm::radians(properties.pitch));
	properties.forward = glm::normalize(dir);
	// Update the back value
	properties.back = -properties.forward;
	// Update the right value
	properties.right = glm::normalize(glm::cross(properties.forward, properties.local_up_direction));
	// Update the left value
	properties.left = -properties.right;

	// Apply these after everything else so any properties that are changed are applied
	apply_transformations(ren);
}

void gearworks::elem_camera::apply_transformations(renderer *renderer) {
	mat4 applied_transformations = mat4(1.0f);

	// Apply position / translation
	renderer->view_matrix = glm::lookAt(properties.position, properties.position + properties.forward, properties.local_up_direction);

	// Clamp the rotation values
	if (properties.yaw >= 360) properties.yaw = -359;
	else if (properties.yaw <= -360) properties.yaw = 359;
	if (properties.pitch >= 360) properties.pitch = -359;
	else if (properties.pitch <= -360) properties.pitch = 359;
	if (properties.roll >= 360) properties.roll = -359;
	else if (properties.roll <= -360) properties.roll = 359;

	renderer->update_renderer();
}