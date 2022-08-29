import ngrok

# construct the api client
client = ngrok.Client("2DuehgT9leFiPs0kktBOrtHK8PO_6GNn6X9DbEg4g2NJHV9is")

# list all online tunnels
for t in client.tunnels.list():
    print(t)

# create an ip policy the allows traffic from some subnets
policy = client.ip_policies.create()
for cidr in ["24.0.0.0/8", "12.0.0.0/8"]:
    client.ip_policy_rules.create(cidr=cidr, ip_policy_id=policy.id, action="allow")




