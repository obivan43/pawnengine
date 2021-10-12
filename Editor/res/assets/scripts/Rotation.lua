function create()
end

function update(dt)
	local angle = 10.0 * dt
	local entity = GameEntity.new(current_entity())
	local entityTransform = entity.transformation

	entityTransform.rotation.x = entityTransform.rotation.x + angle
	entityTransform.rotation.y = entityTransform.rotation.y + angle * 5.0
	entityTransform.rotation.z = entityTransform.rotation.z + angle
	entity.transformation = entityTransform
end
