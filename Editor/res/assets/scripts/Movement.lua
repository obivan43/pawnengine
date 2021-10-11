function create()
end

function update(dt)
	local speed = 5.0 * dt
	local object = GameEntity.new(current_entity())
	local transformation = object.transformation

	local viewForwardMovingVector = vec3MulScalar(transformation.viewForward, speed)
	local viewForwardUpCrossMovingVector = vec3MulScalar(transformation.viewForwardUpCross, speed)

	if keyboard_buttonPressed(Button.W) then
		transformation.position = transformation.position - viewForwardMovingVector
		object.transformation = transformation
	end

	if keyboard_buttonPressed(Button.S) then
		transformation.position = transformation.position + viewForwardMovingVector
		object.transformation = transformation
	end

	if keyboard_buttonPressed(Button.A) then
		transformation.position = transformation.position + viewForwardUpCrossMovingVector
		object.transformation = transformation
	end
	
	if keyboard_buttonPressed(Button.D) then
		transformation.position = transformation.position - viewForwardUpCrossMovingVector
		object.transformation = transformation
	end
end
