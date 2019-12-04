file = io.open("input", "r")
wire1 = file:read()
wire2 = file:read()

function new_point(x, y)
    return {x = x, y = y}
end

function get_wire_points(wire)
    local wire_points = {{x=0, y=0}}

    local counter = 1
    for word in string.gmatch(wire, '([^,]+)') do
    	local prevPoint = wire_points[counter]

        local direction, value
        direction = word:match "%u"
        value = word:match "%d+"
        value = tonumber(value)

        local point = {x = prevPoint.x, y = prevPoint.y}
        if direction == "R" then
           point.x = point.x + value
        elseif direction == "L" then
           point.x = point.x - value
        elseif direction == "U" then
           point.y = point.y + value
        elseif direction == "D" then
           point.y = point.y - value
        end
        table.insert(wire_points, point)

        counter = counter + 1
    end

    return wire_points
end

function print_point(p)
    print(string.format("x: %5d, y: %5d", p.x, p.y))
end

function get_line_segments(wire_points)
	local segments = {}
	for i = 1, #wire_points - 1 do
		local p, nextP = wire_points[i], wire_points[i+1]
		table.insert(segments, {a = p, b = nextP})
	end
	return segments
end

wire_a = get_wire_points(wire1)
wire_b = get_wire_points(wire2)

local segments_a = get_line_segments(wire_a)
local segments_b = get_line_segments(wire_b)

function test_segments(segment1, segment2)
	local x1 = math.min(segment1.a.x, segment1.b.x)
	local x2 = math.max(segment1.a.x, segment1.b.x)
	local y1 = math.min(segment1.a.y, segment1.b.y)
	local y2 = math.max(segment1.a.y, segment1.b.y)

	local x3 = math.min(segment2.a.x, segment2.b.x)
	local x4 = math.max(segment2.a.x, segment2.b.x)
	local y3 = math.min(segment2.a.y, segment2.b.y)
	local y4 = math.max(segment2.a.y, segment2.b.y)

	if y1 == y2 and x3 == x4 then
		if x1 < x3 and x2 > x3 and y3 < y1 and y4 > y1 then
			return true
		end 
		return false
	elseif x1 == x2 and y3 == y4 then
		if y1 < y3 and y2 > y3 and x3 < x1 and x4 > x1 then
			return true
		end
	end
	return false
end

local intersects = {}
-- iterate over each line segment and determine which ones
-- intersect.
-- calculate the final intersection point.
for i = 1, #segments_a do
	local s1 = segments_a[i]
	for j = 1, #segments_b do
		local s2 = segments_b[j]
		local r = test_segments(s1, s2)
		if r then
			local p = {}
			if s1.a.x == s1.b.x then
				p.x = s1.a.x
			end
			if s2.a.x == s2.b.x then
				p.x = s2.a.x
			end
			if s1.a.y == s1.b.y then
				p.y = s1.a.y
			end
			if s2.a.y == s2.b.y then
				p.y = s2.b.y
			end
			table.insert(intersects, math.abs(p.x) + math.abs(p.y))
		end
	end
end

table.sort(intersects)
print("Manhattan distance from closest intersection: ", intersects[1])