function create()
end

function update(dt)

	local camera = GameEntity.new(current_entity())

	if keyboard_buttonPressed(Button.W) then
		local transformation = camera.transformation
		transformation.position.z = transformation.position.z + 1.0 * dt
		camera.transformation = transformation
	end
	
end
