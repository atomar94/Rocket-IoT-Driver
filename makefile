all: server client

server:
	g++ -g main_server.cpp Networking/server.cpp Networking/client.cpp Networking/http_req.cpp Networking/http_res.cpp -o mserver

client:
	g++ -g main_client.cpp Networking/server.cpp Networking/client.cpp Networking/http_req.cpp Networking/http_res.cpp -o mclient

clean:
	rm mclient mserver
