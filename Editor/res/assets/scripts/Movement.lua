function clamp(low, n, high) return math.min(math.max(n, low), high) end

function create() end

function update(dt)

	-- general stuff

	local speed = 5.0 * dt
	local mouseSpeed = 25.0 * dt
	local object = GameEntity.new(current_entity())
	local transformation = object.transformation

	local viewForwardMovingVector = vec3MulScalar(transformation.viewForward, speed)
	local viewForwardUpCrossMovingVector = vec3MulScalar(transformation.viewForwardUpCross, speed)

	-- keyboard handling

	if keyboard_buttonPressed(Button.W) then
		transformation.position = transformation.position - viewForwardMovingVector
	end

	if keyboard_buttonPressed(Button.S) then
		transformation.position = transformation.position + viewForwardMovingVector
	end

	if keyboard_buttonPressed(Button.A) then
		transformation.position = transformation.position + viewForwardUpCrossMovingVector
	end
	
	if keyboard_buttonPressed(Button.D) then
		transformation.position = transformation.position - viewForwardUpCrossMovingVector
	end

	-- mouse handling

	local mouseX = mouse_getRawMouseX()
	local mouseY = mouse_getRawMouseY()

	-- rotation.x is a pitch
	-- rotation.y is a yaw
	-- thats why we use mouseX in rotation.y and mouseY in rotation.x
	transformation.rotation.x = transformation.rotation.x + mouseY * mouseSpeed
	transformation.rotation.y = transformation.rotation.y + mouseX * mouseSpeed

	object.transformation = transformation
end
