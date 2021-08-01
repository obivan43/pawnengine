function create()

end

function update(dt)

	if keyboard_buttonPressed(Button.W) then
		local transform = TransformationComponent.new()
		transform.position = vec3.new(5.0, 4.0, 1.0)
		logger_info("X: " .. transform.position.x)
		logger_info("Y: " .. transform.position.y)
		logger_info("Z: " .. transform.position.z)
	end
	
end
