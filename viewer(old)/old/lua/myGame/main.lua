--love.filesystem.setRequirePath("?.lua;?/init.lua")

time = require 'time'

function love.load()
	isFile = love.filesystem.isFile('time.so')
	--t = time.new_table()
end

function love.draw()
	if isFile then
		love.graphics.print('true', 400, 300)
	end
	love.graphics.print(love.filesystem.getRequirePath(), 0, 16)
	--love.graphics.print(t.hello, 400, 300)
end
