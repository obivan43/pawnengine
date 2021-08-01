function create()
	local camera = GameEntity.new(current_entity())
	local transformation = camera.transformation

	transformation.position.z = 4.0
	camera.transformation = transformation
end

function update(dt)
	local cameraSpeed = 5.0 * dt
	local camera = GameEntity.new(current_entity())
	local transformation = camera.transformation

	local viewForwardMovingVector = vec3MulScalar(transformation.viewForward, cameraSpeed)
	local viewForwardUpCrossMovingVector = vec3MulScalar(transformation.viewForwardUpCross, cameraSpeed)

	if keyboard_buttonPressed(Button.W) then
		transformation.position = transformation.position - viewForwardMovingVector
		camera.transformation = transformation
	end

	if keyboard_buttonPressed(Button.S) then
		transformation.position = transformation.position + viewForwardMovingVector
		camera.transformation = transformation
	end

	if keyboard_buttonPressed(Button.A) then
		transformation.position = transformation.position + viewForwardUpCrossMovingVector
		camera.transformation = transformation
	end
	
	if keyboard_buttonPressed(Button.D) then
		transformation.position = transformation.position - viewForwardUpCrossMovingVector
		camera.transformation = transformation
	end
end
