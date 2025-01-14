IPv4:
    Classful network design for IPv4 sized the networks prefix as one or more 8-bit groups, resulting in the blocks of 8, 16, or 24 bits (of Class A, B, or C networks)
    Under CIDR address space is allocated to Internet Service Providers and end users on any address bit boundary, instead of on 8-bit segments
-> Which service models does Amazon Web Service provide?
    -> Infrastructure as a Service (IaaS)
    -> Platform as a Service (PaaS)
    -> Software as a Service (SaaS)
EC2
    -> An EC2 instance runs in a specific --Availability Zone (AZ)-- based on which --both public and private-- IP addresses are assigned to the instance
    -> You can choose the AZ in which an EC2 will run by:
        -> selecting a subnet for that specific AZ
    -> Software can be automatically installed during the provisioning of the EC2 instace through --User Data-- which is composed of --A series of shell commands--
    -> An EC2 instance can be secured by using --security groups-- which --control the inbound and outbound traffic--
    -> An EC2 instances is deployed in a specific AZ: True
    - An EC2 instance can be configured as follows
        -> based on an instance type which offers certain resources (vCPU,RAM, networking, etc)
    -> Software can be automatically installed during the provisioning of the EC2 instance through --?User Data?-- which is composed of --A series of shell commands--.

    -> The connection times out while trying to access an EC2 instace via SSH on the standard port. What is the most likely issue?
        - The security group does not explictily allow traffic on port 22
    - If you need just one EC2 instance, would an auto-scaling group (ASG) provide any benefit?
        -> Yes, the ASG will ensure there is alyways one instance running

    -> An AWS availability zone is --An iolated location, parat of a specific region, in which resources can be deployed--
    -> An AWS Region is --An independent and isolated cloud deployed in a specific gegraphical region--
    -> An AWS Region is --An AWS data center--
    Elastic Compute Cloud
    it is a web service that provides resizable compute capacity in the cloud. It is designed to make web-scale cloud computing easier for developers.


AWS Virtual Private Cloud (VPC)
    -> VPCs allow you to control the traffic between --(sub)networks-- and use --private IPs--
    Lets you provision a logically isolated section of the AWS Cloud where you can launch AWS resources in a virtual network that you define.
    You have complete control over your virtual networking environment, including a selection of your own IP address range, creation of subnets, and
        configuration of route tables and network gateways.
    You can use both IPv4 and IPv6 in your VPC for secure and easy access to resources and applications.

    Basically, VPCs allow you to control the traffic between (sub)networks and use private IP addresses.

Subnets
    How IP addresses are constructed makes it relatively siimple for Internet routers to find the right network to route data into. However, in a network
        with many IP addresses, there could be millions of connected devices, and it could take some time for the data to find the right device. Subnetting narrows
        down the IP address to use within a range of devices.
    Because an IP address is limited to indicating the newtork and the device address, IP addresses cannot be used to  indicate which subnet an IP packet should go to.
    Routers within a network use something called a subnet mask to sort data into subnetworks.
    Basically, subnets are a way to divide a network into smaller networks. You will create one or more subnets in a VPC.

    The Private Subnet
        A subnet is a sub-range of IP addresses within the VPC. AWS resources can be launched into a specified subnet. Use a public subnet for resources that must be connected
            to the internet and use a pivate subnet for resources that are to remain isolated from the internet.
            VPC ID 
            Name
            AZ
            IPv4 CIDR block

Security groups
    -> You are designing a three-tier web application and want to restict access to the database tier (remember PostgreSQL instace)
        to accept traffic from three application servers only (Spring Java app). However, these application servers are in an 
        Auto Scalling group and may vary in quantity. How should you configure the database servers to meet the reqs?
        - Configure the db sg to allow db traffic from the app server sg
    -> The connection times out while trying to access an EC2 instace via SSH on the standard port. What is the most likely issue?
        - The security group does not explictily allow traffic on port 22
    -> If you need just one EC2 instance, would an auto-scaling group (ASG) provide any benefit?
        -> Yes, the ASG will ensure there is alyways one instance running
    A security group acts as a virtual firewall for your instance to control inbound and outbound and outbound traffic. When you launch an instance in a VPC, you can assign
        up to five security groups to the instance. Security groups act at the instance level, not the subnet level. Therefore, each instance in a subnet in your VPC can be
        assigned to a different set of security groups.
        
    Name
    Description
    Inbound rules
    1 for DB, 1 for App

Load balancers
    -> The AWS service for load balancing supports the following types of load balancers:
        -> Application load balancer which operates at --OSI Layer 7 (HTTP/WebScokets)--
        -> Network load balancer which operates at --OSI Layer 4 (TCP/UDP)--
    Load balancing refers to the process of distributing a set of tasks over a set of resources (computing units), with the aim of making their overall processing more efficient.
    Elastic Load Balancing, the AWS service for loading balancing, supports the following types of load balancers:
        Application:
            This is an actual proxy between the internet and your application. It receives a request from client and makes another request (with the same data) to your application.
            It offers tons of features and it suits very well in most cases. One important tip about it is that since the AB creates another request, but, for some reason, you 
                need the IP address of the original client, you can look at the request header x-forwarded-for.
        Network:
            You can look at it like a (very sophisticated) network router. While the ALB operates at layer 7 (HTTP, WebScokets) of the OSI model, the NLB handles traffic at
                layer 4(TCP, UDP) thus working with packets. You lose some features of the ALB, but gain massive performance (and scalability) and the request looks like it came
                direclty from the original client.
            Also, interestly enough, it is cheaper than an ALB.
        Classic: oldest one and it is deprecated
        Gateway: (new)
            It operates at layer 4 (network). You can use this if you need to integrate other virtual appliances such as deep packet inspection systems.
    
    Listener - port 80(HTTP)
    Targeted groups

Auto Scalling Groups (ASG)
    -> Your application tier is running in an Auto Scalling group and you need to change the instance type. In which of the follwing area can this be achived?
        -> Auto scalling launch template/configuration
    contains a collection of Amazon EC2 instances that are treated as a logical grouping for the purposes of automatic scaling and management. An ASG also enables you to use Amazon
        EC2 Auto Scaling features such ashealth check replacements and scaling policies. Both maintaining the nubmer of instances in an Auto Scaling group and automatic scaling 
        are the core functionality of the Amazon EC2 Auto Scaling service.
    
    Name
    Subnet
    Capacity

AWS provides each account with a default VPC out of the box for each region. This VPC has a certain number of subnets, one for each availability zone of the region.

Cloud Formation
    AWS service to provision and manage our db and app instances in a VPC. It allows us to create templates that define the resources we want to create and how they are configured.

    Name
    Auto Scaling
    AMI - Amazon Machine Image
    App Security Group

Amazon S3 - it stores data (objects) in buckets
    -> The most cost-effective and scalable way to host a static web application on AWS is --Simple Storage Service (S3)--
    -> Simple Storage Service (S3) helps us --Store and serve an infinte amount of objects such as images, documents, and videos--
    -> CloudFront can serve the following
        -> HTTP Traffic from API Gateway
        -> Content stored on S3
        -> HTTP Traffic from Apps hosted on other providers
    -> Documents are stored in S3 in a --Bucket--
    -> Simple Storage Service (S3) works through --HTTP--
    -> Objects stored in S3 can be made public by configuring the --Bucket Policy-- 
        -> (wrong answer) while the objects are uploaded
        -> (wrong anwser) after the objects are uploaded

    It is durable, available and you can store infinite amount of data
    It works with HTTP(S). But for hosting, it does not support HTTPS, so you need to use CloudFront
    Each bucket has his own URL
    Object storage doesn't allow to update/edit files
    Buckets are private by default.

    Access to S3 buckets can be configured using any of:
        ACL
        Resource policy
        IAM policy

CDN - Content Delivery Network
    serves files as fast as possible around the glove
    highly distributed network, thus being geographically closer to the user

    Origin Access Identity - restricts access to the S3 bucket only through CloudFront
    AWS's CDN is called CloudFront

Cloud Front Distribution
    -> CloudFront can serve the following
        -> HTTP Traffic from API Gateway
        -> Content stored on S3
        -> HTTP Traffic from Apps hosted on other providers
    -> CloudFront is a(n) --Content Delivery Network (CDN)-- and is composed of --a network of edge Locations--
    network is made of edge locations
    distribute any HTTP-accessible data, including our website hosted on S3

    Name
    Restrict Bucket Access
    Origin Access Identity
    Read Permissions on Bucket, so CloudFront can update the bucekt policy automatically

Viewer Protocol Policy
    we need a domain to redirect all http traffic to https

Relational Database Service (RDS)
    -> RDS can
        -> upgrade the RDBMS automatically
        -> encrypt the data
        -> backup the database automatically
    -> RDS is --managed relational database service--

    We choose the hardware specs and database engine that we need, security and availability, RDS it will run and manage the db for us
    RDS supports MySQL, PostgreSQL, Oracle, SQL Server, MariaDB, and Aurora

    Name
    DB instance size and storage
    Connectivity (to the db instance using the security group)

Docker 
    -> Docker is a --container engine--
    -> What is the difference between a Docker image and a Docker container?
        -> Containers are running instances of the images
    -> From where does Docker pull the image hello-world when running docker run hello-world
        -> Always pulls it from the Docker Hub

    is a container engine. Isolated environment where we can run programs.
    a VM , an environment containing and running our app together with all its dependencies and it is based on images (if container are objects, images are classes)
    We will use EC2 instances to run our Docker containers

Amazon ECR 
    Elastic Container Registry
    is a fully managed Docker container registry that makes it easy for developers to store, manage, and deploy Docker container images.
    here we push the image to container registry

Amazon ECS
    Elastic Container Service
    is a fully managed container orchestration service that makes it easy to run, stop, and manage Docker containers on a cluster.
    here we run the container

    you manually starts the container or create an ECS service

IAM Concepts
    Users
        entities that interact with the AWS resources under your account. A set of credentials that offer access to the AWS APIs/console
        no predefined users in AWS
    Group
        groups of users
        maintain the permissions for multiple users
        no predefined groups in AWS
    Policies
        JSON documents that define permissions
        can be attached to users, groups, or roles
            Identity-based policies - they specify what the entity having it attached can do.
            Resource-based policies - they are attached to resources (S3 buckets) and describe who/what has access to it and to what extnt - the who/what is called the principal
        you can have policies for policies and Service Control Policies (SCPs) that are applied at the organization level
    Roles
        they can be assumed by anentity
        you can use roles to provide temporary access to AWS resources of your account to your applications or to external users
        you can attach policies to roles
        roles can be assumed by resources such as EC2 instances, or by users
        
Frontend
    UI frameworks like React, Angular, Vue, Polymer, Svelte generates static files (HTML, CSS, JS) and load the data from backend(usually through https requests - AJAX) so
        the host doesn't have to do any processing other than sending the files as they are to the client/requester

OSI model
    Layer 1: Physical
    Layer 2: Data Link
    Layer 3: Network
    Layer 4: Transport (TCP, UDP)
    Layer 5: Session
    Layer 6: Presentation
    Layer 7: Application - the layer that the user interacts with (HTTP, WebSockets)

