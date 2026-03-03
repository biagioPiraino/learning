### Course reference

[YT course](https://www.youtube.com/watch?v=kTp5xUtcalw)


containers / dockers / kubernetes

### Microservices concepts
loosely coupled services, fine grained and lightweight communication (usually grpc)

segregates functionality and sresponsibiility
piece can scale independnetly
different team, different languages, different database
deployed and scale independelty

break in small unit
strangler facade pattern for migration -> martin fawler blog


antipaterns:
    unnecessary complexity
    overnegineering
    security issues
    processes and overhead
    new figures required
    not magic, comes with complexity
    
Pro and cons:
improved fault isolation
eliminate vendor or tech lock in
easier and faster to deploy and sclae

complexity
system and integration testing harder
multiple database to manage
latency issues
transient errors
processes added for deployment
multiple point of failure
security


### Cloud native
uses container services, meshes Microservices, immutable adn disposable infrastructure (never update but replaced with new version) and declerative api
loosly copplple system, automation , frequent deployment
ecosystem run on opensource project (like kubernetes)

is about spped and agility in deployment
clean code -> ddd -> microservices -> kube

easier with new project

check the cloud native map from the cloud native foundation (trail map)

### Containers introduction
faster to deploy
run everywhere
isolated
faster automation

vm virtualise hardware with os, container virtualise an operating system (they do not boot)

vm large footprint, slow to boot, ideal for running tasks
c quick lightweight portable for short lived tasks, pack more contaienr on same server (more density)

contianer, layering:
    base os + customisation (pkgs) + application
    
docker pull for getting an image

conatiner registry
    centralisd repo for containers
    
orchestrator
    manage infrastructure. contaienr, deployment, scaling, faiover, helth monitoring, app upgrade and zero downtime
    
    
### Docker
contaier runtime
command line tool
dockerfile for building containers

docker desktop easier starting point
    you can have the remote hub for having images saved in the cloud
    like git and github

cli
    docker info -> system info, all container and system information
    docker version -> system version, for docker engine
    docker login -> log in docker registry (default to docker hub)
    docker pull <image-name> -> pull image from registry
    docker run (-d) <image-name> -> run containers (detached)
    docker start <container-name>-> start stopped containers
    docker stop <container-name>-> stop running containers
    docker ps (-a) -> list running (and stopped) containers
    docker kill <container-name> -> kill containers, usually not used
    docker image inspect <image-name> -> get image info
    docker run --memory="256m" <image-name> -> max memory
    docker run --cpus=".5" <image-name> -> max cpu
    docker rm <container-name> -> remove stopped container from memory
    docker rm $(docker ps -a -q) -> remove all stopped conatiners from memory
    docker images -> list local image
    docker rmi <image-name> -> remove the image
    docker run -it <image-name> -- /bin/bash -> attach shell
    docker container exec -it <container-name> -- bash -> attach to a running container
    
    # example
    docker run --publish 80:80 --name <container-name> <image-name>
    
Docker Image: A read-only blueprint or snapshot. It contains everything an application needs to run: the code, libraries, dependencies, and environment settings. It is "frozen" and cannot be changed once built.

Docker Container: A live, running instance of an image. When you "run" an image, it becomes a container. Unlike an image, a container is a process that exists in memory and has a writable layer where it can store temporary data. 

Tagging as latest

todo:
Adding aliases inside the container? How to?


build containers
    docker build -t [name:tag] . -> dockerfile in current directory
    docker build -t [name:tag] -f <filename> -> dockerfile in != location
    docker tag <image-name> [name:tag] -> tag an existing image, sepcify version number
    
Dockerfile contains building steps for creating and run the containers

Tagging
    creat a target image
    name:tag
    repository/name:tag -> in case of remote or differnte repository
