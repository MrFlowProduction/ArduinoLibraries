/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C" {
#endif

const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n\
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n\
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n\
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n\
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n\
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n\
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n\
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n\
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n\
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n\
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n\
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n\
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n\
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n\
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n\
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n\
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n\
rqXRfboQnoZsG4q5WTP468SQvvG5\n\
-----END CERTIFICATE-----\n"};

const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWTCCAkGgAwIBAgIUZnN2+SRHkWRi2M5PB4syzyhOYcAwDQYJKoZIhvcNAQEL\n\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MTExMTA4MjMw\n\
NloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n\
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKdN0M+zSFJHez4p6LBt\n\
OoFcP3ijjzmRMNZCojvEUAHV5NyNrD+u5AuDHoJAS4uP+BayQ4CgMzKn32MJQK+i\n\
bmiLuA2mnSs0aH5JvsoGqMlUonlvaGxXjkc2WvypHAw5Ec60OuxNEcEb/hZLiaMB\n\
6YMYPjxM84gKj6GhTArGpT3wyWb9rToftUnojms+WOw+Ce2Uw5iaCG1RWqeR1/nS\n\
MIuDLjN8uLN+uokBPC+ypT0MgI+8MDbQQbBzsPAPt/DsusnFkYFv03ilaEA7vcfD\n\
huUAXEQ/4/dcJ6N2nX2AiP3gu40YXGYb51I5Gb6bYFXoVO2E+6E7PCOgYGcpdA0/\n\
gx8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUW4uZU2K0A2jmDLN8U+Ue4sOWEQowHQYD\n\
VR0OBBYEFH5lVBg5Zr8kmErK90jPuyMZNSiGMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n\
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBeoYDW+EpGiQh9ne889AIhCUHC\n\
N/ie5pAqhtMqcAd0PcXyQw4BnAaETD0rEx3u8R+RQbTlEZlemIiiQrtlWpJgdz18\n\
MKcFD2WG3P4hhXT0WkKw0aJSiCP2cl0w0C8HJdRwugRKmoU54EfJiSaFi9DjuMdj\n\
q+pgY8/00JCS2PDGLoEp/2RzZ32QheE7emqECsuUNEDs7hbUHJJRg9H9k+msGhrt\n\
1JWF03AA4tJ7Rgtq/TuYyFhe2MDoasRlkDAidGA1S5q8L7ftHroLcS3HG4ZEEyNN\n\
ZvVRriPlkv19GpUR3P8s9hGSeFn4azkUxWvvqhUHKtF5/VzXTvDZK+vIYQPj\n\
-----END CERTIFICATE-----\n"};

const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEogIBAAKCAQEAp03Qz7NIUkd7PinosG06gVw/eKOPOZEw1kKiO8RQAdXk3I2s\n\
P67kC4MegkBLi4/4FrJDgKAzMqffYwlAr6JuaIu4DaadKzRofkm+ygaoyVSieW9o\n\
bFeORzZa/KkcDDkRzrQ67E0RwRv+FkuJowHpgxg+PEzziAqPoaFMCsalPfDJZv2t\n\
Oh+1SeiOaz5Y7D4J7ZTDmJoIbVFap5HX+dIwi4MuM3y4s366iQE8L7KlPQyAj7ww\n\
NtBBsHOw8A+38Oy6ycWRgW/TeKVoQDu9x8OG5QBcRD/j91wno3adfYCI/eC7jRhc\n\
ZhvnUjkZvptgVehU7YT7oTs8I6BgZyl0DT+DHwIDAQABAoIBAGlPDfTvAMLpw6Wp\n\
c5I57u2mRz2Elo7B2V/EqaG9PC8rl9dMRfP//gNREU8jcWnzwVFn/B1muVNVX8NS\n\
+6iSMbUU3VGaYqvjXTLA8Jrx/iRcZbjSa4RmyGQCztrjB4iaE59syvoauOY43ILk\n\
IUq91WJzTBlgxpoHK8mtYdQWncSSW2oae34KOuvAnpHcESBQO5kGOC5Ai3RNJpPL\n\
MU04TwWtecafnuNs8H0C85Q/+sd5VYt9GBXTyB+zz5msFO4n0gWpyls05eJgYtGK\n\
NqDCfVKFq9t2bNfCO5+6Vms7wiVZqe2iDseyDllW/i2eNOU5/w0run2oDmiXhwSx\n\
VIjLi8ECgYEAz6AmG8Ayf0FtGGp0XxTnUhE/s3Xitez1YB5Li5JtwrKah4CCw5ow\n\
949ZfjZAnCg4PS86ys7vqOav8YF2YHOSq9Hq0qY7gTcqbURGwhRrKs46ygMtW9bJ\n\
GG1Q1Q6VEkq7jxTyR22leoS0K0MkfAItxKtQStRggJBJvOrY/rzVOscCgYEAzkit\n\
+tJvU9VTKKOcmxB/bbTaNNI14mUy+ltKlgbFYumvotN8ZKJ6GJpDhx7U6WK/euBN\n\
ix5gjCgK/oXijbbP/dscTZUiMZfZuPfBZl8dGB4AYxuzFdQTWUVzg+/P84DOJgtm\n\
LCT3EfRI1oY13WFQWBB+Kz5hExj5Qbsp//AG3OkCgYAPhTY0Dtr3fkmMcLDARsy/\n\
6sArRx2qYcs54ynchhakXjuE84tS2dzdNJ8I+z87LRp/IF+xt2Rc6NmwIPBbZ2hI\n\
Zcm682gxUZFfV6I+cc5NBduJLFGgst6Xb9yCALQOCP4aRQOTaVPcY70gGsXIa1VG\n\
hVPcNCH+mkqYz6lm6XC7EwKBgAa17pL+TYjYo7/qsqmIu9yByad2PzKCQEpMtfxz\n\
c/Bn0cLmRmGvt3Edc5ztr9d30urYaS1ha5qjotfs2xXpIJMNkbokY9xhKEAQL0Z5\n\
SaUDNNgEiqrnH0oELGHaZ1Vwl0Q9krFU8oSvAb+Y1h/Bjq+OucwGV3obkeBFinQ9\n\
BrwhAoGASACeTo+1+bR41kKKfEDlMdabp7AvRAMDwsjwr/bbHqyogTKHeM9EMa0d\n\
Tq9+Fvon5i5h3coaCM0pcxDN6CBS2pya8UuT88DaxHElT9nzk1uUGx/REzguup5b\n\
Rt3eRhkV4kHPYqeH0kNnUQjTJgPQWz3wkjHnA0/0fXml3aCtRsM=\n\
-----END RSA PRIVATE KEY-----\n"};


#ifdef __cplusplus
}
#endif
