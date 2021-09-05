#include "e_default.h"

void elem_default::apply_transformations(gearworks::renderer *renderer) {
	// Create an identity matrix to store the applied transformations
	mat4 applied_transformation = mat4(1.0f);

	// Add the active translation to the stored transformations variable
	applied_transformation = glm::translate(applied_transformation, properties.position);

	// Add the active rotation to the stored transformations variable, with the given axes being affected
	if (properties.rotation.z != 0) applied_transformation = glm::rotate(applied_transformation, glm::radians(properties.rotation.z), vec3(0, 0, 1));
	if (properties.rotation.y != 0) applied_transformation = glm::rotate(applied_transformation, glm::radians(properties.rotation.y), vec3(0, 1, 0));
	if (properties.rotation.x != 0) applied_transformation = glm::rotate(applied_transformation, glm::radians(properties.rotation.x), vec3(1, 0, 0));

	// Add the active scale to the stored transformations variable
	applied_transformation = glm::scale(applied_transformation, vec3(properties.scale));

	// Clamp the rotation values
	if (properties.rotation.x >= 360) properties.rotation.x = -359;
	else if (properties.rotation.x <= -360) properties.rotation.x = 359;
	if (properties.rotation.y >= 360) properties.rotation.y = -359;
	else if (properties.rotation.y <= -360) properties.rotation.y = 359;
	if (properties.rotation.z >= 360) properties.rotation.z = -359;
	else if (properties.rotation.z <= -360) properties.rotation.z = 359;

	// Apply these changes to the renderer by setting its model matrix and then updating it
	renderer->model_matrix = applied_transformation;
	renderer->update_renderer();

	// Reset the translation of the model matrix back to 0
	// This step ensures that the object rotates around its local origin, rather than the world space origin
	applied_transformation = glm::translate(applied_transformation, vec3(0.0f));

	// Then apply this change to the renderer.
	renderer->model_matrix = applied_transformation;
	renderer->update_renderer();
}

elem_default::shape_properties_struct::shape_properties_struct() :
	colour(NULL),
	opacity(255),
	position(vec3(0)),
	rotation(vec3(0)),
	scale(vec3(1)) 
{}