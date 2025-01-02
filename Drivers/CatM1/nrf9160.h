/*
 * nrf9160.h
 *
 *  Created on: Oct 3, 2024
 *      Author: phb10
 */

#ifndef CATM1_NRF9160_H_
#define CATM1_NRF9160_H_

#include "stm32u5xx_hal.h"
#include <stdbool.h>

#include <time.h>

#include "cmsis_os2.h"
//DK
//// CA Certificate
//#define caCert "AT%CMNG=0,16842753,0,\"-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----\n\"\r\n"
//
//// Client Certificate
//#define clientCert "AT%CMNG=0,16842753,1,\"-----BEGIN CERTIFICATE-----\nMIICuDCCAaACCQD1sW5ydunD5DANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJO\nTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNVBAoM\nFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4Yjkw\nMCAXDTI0MTAzMTA3MDA0OVoYDzIwNTQxMDI0MDcwMDQ5WjCBmDELMAkGA1UEBhMC\nTk8xEjAQBgNVBAgMCVRyb25kZWxhZzESMBAGA1UEBwwJVHJvbmRoZWltMSEwHwYD\nVQQKDBhOb3JkaWMgU2VtaWNvbmR1Y3RvciBBU0ExLTArBgNVBAMMJDUwNGU1NzM3\nLTMyMzUtNDg2YS04MGYwLTBhMmMyZjZiOTgxMjEPMA0GA1UELhMGMTIzNDU2MFkw\nEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEXRdzwrmYtdN35/hLfa2lrUaqWshnl9pH\nKHy8GorLFzQNrqmlVFANXtTUGeRaCG7eMcDqLsuKxtTa0kcJ0QqkLTANBgkqhkiG\n9w0BAQsFAAOCAQEAoKRJCyJK2GN6kGlRcRRJPjEw2GeGwaIuXWGYzrrthHUWzqao\niJQY3OGFhiNyu1q1T4oym6Y5bJTEt95aIs0C/p81H2KslBraO6Tkbd2gonUP3GPL\nIBUBrpnEd95RfSgYU5PdOpFtGOKk0BjI8BTe4I0ml09W6JUHLiznUg75VQoDq/8e\nHVzJ7ypxG1GX0GmaAzi/N3CEwmucScOEMWGOfGkb8tfC9Qzz8ffTuKm3Fpiefd9j\nGHMLN8CpEswmAD75YcbcAkvy8/uUG4gDxQldNwqswnJLxQVjEUr9YPcTTsHhCl62\nx1vNvcAGm31e1qMT+R80VbhzzHOCP+jERc9wQw==\n-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----\nMIIDqzCCApOgAwIBAgIJAOXo6/ALtz+gMA0GCSqGSIb3DQEBCwUAMGwxCzAJBgNV\nBAYTAk5PMQ8wDQYDVQQIDAZOb3J3YXkxEjAQBgNVBAcMCVRyb25kaGVpbTEdMBsG\nA1UECgwUTm9yZGljIFNlbWljb25kdWN0b3IxGTAXBgNVBAsMEEdlbmVyaWMtMTRh\nMThiOTAwHhcNMjMwMzE2MDMzODAwWhcNMjYwMTAzMDMzODAwWjBsMQswCQYDVQQG\nEwJOTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNV\nBAoMFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4\nYjkwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2CE46Te7DvZxfauo\nCZhNGpvJ/RNP5cfunU3qnzhpnpDwbgMT8lU2zMe14kolzNr2LQN09EYSDmBYh5je\nszKUT1FKKvMAs59UnPrdLiwWG6tWhfa5CzsNgMi+TjGcqK8K7D+Gv+b7EzDqtYFM\ng5FovJE6wYO/DIHRq7dVa21B3GB2vqiQZCXuef8kc1NCAXFm2MX5lkV6MQxyXYBo\nV8+/jNTiXSriGFJVG6MvF4lRTKC0TTV2NBFaJmRDwEuBoUSpbNoNDhhNOm+kbVBH\nlfXP81YwNOl+RVNbjGmA2lG3SEf/42jsCiaKjXp1cozF+EKGI8/H7ryMyoq0a3dG\nEFy7zwIDAQABo1AwTjAdBgNVHQ4EFgQU8QcvSXGLHmKmu6LrgIobANmjQ6IwHwYD\nVR0jBBgwFoAU8QcvSXGLHmKmu6LrgIobANmjQ6IwDAYDVR0TBAUwAwEB/zANBgkq\nhkiG9w0BAQsFAAOCAQEAAuXJuAx2BBDh44ljxqQsfLfhDNN3J8LZeoG5wbcSKQw6\nXCBp4BO/oeL8SWZ8G7WmTIxxpWyf5wBEvVGqmUnKj+skRXKVsHon63+ihomGDZTM\nb+lsPJFH0XYvmFhYhRMnDJC5FVyhsyRloyWgmRcsFoXqlkySPD8qN7/EXvHdcQwI\nB4d6mfcN9943Oywh72GdlMPxvmdBsOoRDP46Hb8NoVlEcgvNT4SWfjh6AHZiqO5r\n2NOCvvbO8S2r1NzCXBuBPtm5dY/hmbZOCiTBnK7SX6Aol24rVH7vuYOW0iLv30O2\nqke6pyCrthgdokfe2kd94L/Saos6cR8phmH5SqkZFg==\n-----END CERTIFICATE-----\n\"\r\n"
//// Private Key
//#define privateKey "AT%CMNG=0,16842753,2,\"-----BEGIN EC PARAMETERS-----\nBggqhkjOPQMBBw==\n-----END EC PARAMETERS-----\n-----BEGIN EC PRIVATE KEY-----\nMHcCAQEEICMiomLbCf+AFeIpfO29mhTk+pEyxj4XEMDauVLrwxZpoAoGCCqGSM49\nAwEHoUQDQgAEXRdzwrmYtdN35/hLfa2lrUaqWshnl9pHKHy8GorLFzQNrqmlVFAN\nXtTUGeRaCG7eMcDqLsuKxtTa0kcJ0QqkLQ==\n-----END EC PRIVATE KEY-----\n\"\r\n"

//2
// CA Certificate
#define caCert "AT%CMNG=0,16842753,0,\"-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----\n\"\r\n"

// Client Certificate
#define clientCert "AT%CMNG=0,16842753,1,\"-----BEGIN CERTIFICATE-----\nMIICuDCCAaACCQCJ/d6yIpC6BDANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJO\nTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNVBAoM\nFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4Yjkw\nMCAXDTI0MTEwNTAxMjE0M1oYDzIwNTQxMDI5MDEyMTQzWjCBmDELMAkGA1UEBhMC\nTk8xEjAQBgNVBAgMCVRyb25kZWxhZzESMBAGA1UEBwwJVHJvbmRoZWltMSEwHwYD\nVQQKDBhOb3JkaWMgU2VtaWNvbmR1Y3RvciBBU0ExLTArBgNVBAMMJDUwNDI1MjMz\nLTM1MzUtNGJmYS04MDdkLTEzMWQ3Y2Y2M2Y0ODEPMA0GA1UELhMGMTIzNDU2MFkw\nEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEJS936vzpkEIi9c47s0WXhRKTPCYw5jbf\nlQ+yMy9AZ3qZE6kU3HJlcbOE4PxE9uGsynmalg2Z5OqTYNLNtBLELzANBgkqhkiG\n9w0BAQsFAAOCAQEAIcpgEzJmMNOlXSdqL2DZg4q1yia1pjf5Wr3LuFx13nRR6ZCT\nw/zJPErG5gPLB2j4eg8VR4KJhXWzik/oJz469gJsrThKqy0qx92K34gnHfyv8EyU\nBKiiFHQQBfl8Jd/p7gzbKkzJmSTn5r8NhBpBCnGmbxA2vVY28WA2Vu7n4L+42x7I\nx+wcjtJyGVNmZiZ33tpqe0oxSewcg0kTdaponEWl/lyaOxMC/4LJBP1lQxL7e4N+\nMSXWCXQnIpXXFo0QIeg5fPZc3LT9LBF6DFzmhamK7XdXFeYD8FE2Le8DvQGQrX1Z\niiuH8S7hf4Pm/B7V18AZ8/ASWvrvui+rveo1IQ==\n-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----\nMIIDqzCCApOgAwIBAgIJAOXo6/ALtz+gMA0GCSqGSIb3DQEBCwUAMGwxCzAJBgNV\nBAYTAk5PMQ8wDQYDVQQIDAZOb3J3YXkxEjAQBgNVBAcMCVRyb25kaGVpbTEdMBsG\nA1UECgwUTm9yZGljIFNlbWljb25kdWN0b3IxGTAXBgNVBAsMEEdlbmVyaWMtMTRh\nMThiOTAwHhcNMjMwMzE2MDMzODAwWhcNMjYwMTAzMDMzODAwWjBsMQswCQYDVQQG\nEwJOTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNV\nBAoMFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4\nYjkwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2CE46Te7DvZxfauo\nCZhNGpvJ/RNP5cfunU3qnzhpnpDwbgMT8lU2zMe14kolzNr2LQN09EYSDmBYh5je\nszKUT1FKKvMAs59UnPrdLiwWG6tWhfa5CzsNgMi+TjGcqK8K7D+Gv+b7EzDqtYFM\ng5FovJE6wYO/DIHRq7dVa21B3GB2vqiQZCXuef8kc1NCAXFm2MX5lkV6MQxyXYBo\nV8+/jNTiXSriGFJVG6MvF4lRTKC0TTV2NBFaJmRDwEuBoUSpbNoNDhhNOm+kbVBH\nlfXP81YwNOl+RVNbjGmA2lG3SEf/42jsCiaKjXp1cozF+EKGI8/H7ryMyoq0a3dG\nEFy7zwIDAQABo1AwTjAdBgNVHQ4EFgQU8QcvSXGLHmKmu6LrgIobANmjQ6IwHwYD\nVR0jBBgwFoAU8QcvSXGLHmKmu6LrgIobANmjQ6IwDAYDVR0TBAUwAwEB/zANBgkq\nhkiG9w0BAQsFAAOCAQEAAuXJuAx2BBDh44ljxqQsfLfhDNN3J8LZeoG5wbcSKQw6\nXCBp4BO/oeL8SWZ8G7WmTIxxpWyf5wBEvVGqmUnKj+skRXKVsHon63+ihomGDZTM\nb+lsPJFH0XYvmFhYhRMnDJC5FVyhsyRloyWgmRcsFoXqlkySPD8qN7/EXvHdcQwI\nB4d6mfcN9943Oywh72GdlMPxvmdBsOoRDP46Hb8NoVlEcgvNT4SWfjh6AHZiqO5r\n2NOCvvbO8S2r1NzCXBuBPtm5dY/hmbZOCiTBnK7SX6Aol24rVH7vuYOW0iLv30O2\nqke6pyCrthgdokfe2kd94L/Saos6cR8phmH5SqkZFg==\n-----END CERTIFICATE-----\n\"\r\n"
// Private Key
#define privateKey "AT%CMNG=0,16842753,2,\"-----BEGIN EC PARAMETERS-----\nBggqhkjOPQMBBw==\n-----END EC PARAMETERS-----\n-----BEGIN EC PRIVATE KEY-----\nMHcCAQEEIL0HchYJYkbhHGyk05URmIOpfbgEOyv7505NKMjhgXAPoAoGCCqGSM49\nAwEHoUQDQgAEJS936vzpkEIi9c47s0WXhRKTPCYw5jbflQ+yMy9AZ3qZE6kU3HJl\ncbOE4PxE9uGsynmalg2Z5OqTYNLNtBLELw==\n-----END EC PRIVATE KEY-----\n\"\r\n"

//3
//// CA Certificate
//#define caCert "AT%CMNG=0,16842753,0,\"-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----\n\"\r\n"
//
//// Client Certificate
//#define clientCert "AT%CMNG=0,16842753,1,\"-----BEGIN CERTIFICATE-----\nMIICuDCCAaACCQDOYm2UCnkc+TANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJO\nTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNVBAoM\nFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4Yjkw\nMCAXDTI0MTEwNDExMzEzOFoYDzIwNTQxMDI4MTEzMTM4WjCBmDELMAkGA1UEBhMC\nTk8xEjAQBgNVBAgMCVRyb25kZWxhZzESMBAGA1UEBwwJVHJvbmRoZWltMSEwHwYD\nVQQKDBhOb3JkaWMgU2VtaWNvbmR1Y3RvciBBU0ExLTArBgNVBAMMJDUwNDI1MjMz\nLTM1MzUtNDI0Zi04MDJiLTEzMTExYTkwMjcwYTEPMA0GA1UELhMGMTIzNDU2MFkw\nEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEi4u4R8wgOR3oCCDkGZUZeQcb4qEEbx05\nnT9LkutRI+C3qNE+zUcI3BH+VmwpPxaSTTZedol7OUmUXah1OdsESzANBgkqhkiG\n9w0BAQsFAAOCAQEAdEOl/CC+M+8ebSzS3kXohxb0J3/BCO+QOBsqQ6vT0RJob80s\nXeKWHXpN7S4FZ5+E//gzaig9KBT/7hcQC9WYq86qTBKTdj5iyB81HxrRnVHIGtyQ\nR2lhH4tsxYyI5q3fvZy1LjEWEfzY+OhR7D7xE5U83yOZEOUk17BL4HSHM/4Rs6gW\nq1tAIDdw0Pgegb8MNfT0kF7VJsuDTnrlfnQYN1o61xbGSsyzj1PWQt8Zfbml9Waz\n9lQW5feT591ZRo7/6vPjjEezDAkDL0W062hWSw+QWi7DYJjH3NFPlHZntrTRn9+P\n8eP9RVfc0xZnriozLtNbykb+qxTalTc4ANdzOg==\n-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----\nMIIDqzCCApOgAwIBAgIJAOXo6/ALtz+gMA0GCSqGSIb3DQEBCwUAMGwxCzAJBgNV\nBAYTAk5PMQ8wDQYDVQQIDAZOb3J3YXkxEjAQBgNVBAcMCVRyb25kaGVpbTEdMBsG\nA1UECgwUTm9yZGljIFNlbWljb25kdWN0b3IxGTAXBgNVBAsMEEdlbmVyaWMtMTRh\nMThiOTAwHhcNMjMwMzE2MDMzODAwWhcNMjYwMTAzMDMzODAwWjBsMQswCQYDVQQG\nEwJOTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNV\nBAoMFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4\nYjkwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2CE46Te7DvZxfauo\nCZhNGpvJ/RNP5cfunU3qnzhpnpDwbgMT8lU2zMe14kolzNr2LQN09EYSDmBYh5je\nszKUT1FKKvMAs59UnPrdLiwWG6tWhfa5CzsNgMi+TjGcqK8K7D+Gv+b7EzDqtYFM\ng5FovJE6wYO/DIHRq7dVa21B3GB2vqiQZCXuef8kc1NCAXFm2MX5lkV6MQxyXYBo\nV8+/jNTiXSriGFJVG6MvF4lRTKC0TTV2NBFaJmRDwEuBoUSpbNoNDhhNOm+kbVBH\nlfXP81YwNOl+RVNbjGmA2lG3SEf/42jsCiaKjXp1cozF+EKGI8/H7ryMyoq0a3dG\nEFy7zwIDAQABo1AwTjAdBgNVHQ4EFgQU8QcvSXGLHmKmu6LrgIobANmjQ6IwHwYD\nVR0jBBgwFoAU8QcvSXGLHmKmu6LrgIobANmjQ6IwDAYDVR0TBAUwAwEB/zANBgkq\nhkiG9w0BAQsFAAOCAQEAAuXJuAx2BBDh44ljxqQsfLfhDNN3J8LZeoG5wbcSKQw6\nXCBp4BO/oeL8SWZ8G7WmTIxxpWyf5wBEvVGqmUnKj+skRXKVsHon63+ihomGDZTM\nb+lsPJFH0XYvmFhYhRMnDJC5FVyhsyRloyWgmRcsFoXqlkySPD8qN7/EXvHdcQwI\nB4d6mfcN9943Oywh72GdlMPxvmdBsOoRDP46Hb8NoVlEcgvNT4SWfjh6AHZiqO5r\n2NOCvvbO8S2r1NzCXBuBPtm5dY/hmbZOCiTBnK7SX6Aol24rVH7vuYOW0iLv30O2\nqke6pyCrthgdokfe2kd94L/Saos6cR8phmH5SqkZFg==\n-----END CERTIFICATE-----\n\"\r\n"
//// Private Key
//#define privateKey "AT%CMNG=0,16842753,2,\"-----BEGIN EC PARAMETERS-----\nBggqhkjOPQMBBw==\n-----END EC PARAMETERS-----\n-----BEGIN EC PRIVATE KEY-----\nMHcCAQEEIBPYQq7QvPgTP8NgBon9YmdQEMl7psqom/kko9onUIjPoAoGCCqGSM49\nAwEHoUQDQgAEi4u4R8wgOR3oCCDkGZUZeQcb4qEEbx05nT9LkutRI+C3qNE+zUcI\n3BH+VmwpPxaSTTZedol7OUmUXah1OdsESw==\n-----END EC PRIVATE KEY-----\n\"\r\n"

//5
//// CA Certificate
//#define caCert "AT%CMNG=0,16842753,0,\"-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----\n\"\r\n"
//
//// Client Certificate
//#define clientCert "AT%CMNG=0,16842753,1,\"-----BEGIN CERTIFICATE-----\nMIICuDCCAaACCQCK3Bu6ag1/zDANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJO\nTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNVBAoM\nFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4Yjkw\nMCAXDTI0MTEwMTA1NTk1OFoYDzIwNTQxMDI1MDU1OTU4WjCBmDELMAkGA1UEBhMC\nTk8xEjAQBgNVBAgMCVRyb25kZWxhZzESMBAGA1UEBwwJVHJvbmRoZWltMSEwHwYD\nVQQKDBhOb3JkaWMgU2VtaWNvbmR1Y3RvciBBU0ExLTArBgNVBAMMJDUwNDI1MjMz\nLTM1MzUtNDE5YS04MDdjLTEzMjA3N2YwM2I5MzEPMA0GA1UELhMGMTIzNDU2MFkw\nEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEpdSfGv6PlZl2ADvjslGfU5EjRLVIDxbg\nVDEEK8TDOhWIuncxq+YMd47Bk589bJQ71jFxlPN4nAhKQyy/D63/PTANBgkqhkiG\n9w0BAQsFAAOCAQEABUZFQvdE1cgjmpy+ldkXDPs8DZMODpb30xM6tWOCjKOhcDQ2\np95csNRA5H3Q7LqJ7HZqbkOJtNP5VIS05b3YoYiZdGgFeIf/dPIcyxMhhzy6Ppvm\niMp29R2iqFE/a4r9N6UCJtc9qVafZJ7Ca+ZjmL4cEoogiEKKY8qDyUxB6lfRDocf\nt1HzLoKnUXUUGtS74aAMyJUB4RZK1vvAPCzujY/EcnJ3/g3R9F+OCgsVXl+qn0qA\n5dGokVizB0lEclsYdK6e1qgCg8iR359Yx42yc2FRjrThyA39hgRF1aUDtH0ckDqN\nieeeyfOmYHL/tcsa/EMtmGxw/YzrE66+McNgyA==\n-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----\nMIIDqzCCApOgAwIBAgIJAOXo6/ALtz+gMA0GCSqGSIb3DQEBCwUAMGwxCzAJBgNV\nBAYTAk5PMQ8wDQYDVQQIDAZOb3J3YXkxEjAQBgNVBAcMCVRyb25kaGVpbTEdMBsG\nA1UECgwUTm9yZGljIFNlbWljb25kdWN0b3IxGTAXBgNVBAsMEEdlbmVyaWMtMTRh\nMThiOTAwHhcNMjMwMzE2MDMzODAwWhcNMjYwMTAzMDMzODAwWjBsMQswCQYDVQQG\nEwJOTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNV\nBAoMFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4\nYjkwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2CE46Te7DvZxfauo\nCZhNGpvJ/RNP5cfunU3qnzhpnpDwbgMT8lU2zMe14kolzNr2LQN09EYSDmBYh5je\nszKUT1FKKvMAs59UnPrdLiwWG6tWhfa5CzsNgMi+TjGcqK8K7D+Gv+b7EzDqtYFM\ng5FovJE6wYO/DIHRq7dVa21B3GB2vqiQZCXuef8kc1NCAXFm2MX5lkV6MQxyXYBo\nV8+/jNTiXSriGFJVG6MvF4lRTKC0TTV2NBFaJmRDwEuBoUSpbNoNDhhNOm+kbVBH\nlfXP81YwNOl+RVNbjGmA2lG3SEf/42jsCiaKjXp1cozF+EKGI8/H7ryMyoq0a3dG\nEFy7zwIDAQABo1AwTjAdBgNVHQ4EFgQU8QcvSXGLHmKmu6LrgIobANmjQ6IwHwYD\nVR0jBBgwFoAU8QcvSXGLHmKmu6LrgIobANmjQ6IwDAYDVR0TBAUwAwEB/zANBgkq\nhkiG9w0BAQsFAAOCAQEAAuXJuAx2BBDh44ljxqQsfLfhDNN3J8LZeoG5wbcSKQw6\nXCBp4BO/oeL8SWZ8G7WmTIxxpWyf5wBEvVGqmUnKj+skRXKVsHon63+ihomGDZTM\nb+lsPJFH0XYvmFhYhRMnDJC5FVyhsyRloyWgmRcsFoXqlkySPD8qN7/EXvHdcQwI\nB4d6mfcN9943Oywh72GdlMPxvmdBsOoRDP46Hb8NoVlEcgvNT4SWfjh6AHZiqO5r\n2NOCvvbO8S2r1NzCXBuBPtm5dY/hmbZOCiTBnK7SX6Aol24rVH7vuYOW0iLv30O2\nqke6pyCrthgdokfe2kd94L/Saos6cR8phmH5SqkZFg==\n-----END CERTIFICATE-----\n\"\r\n"
//// Private Key
//#define privateKey "AT%CMNG=0,16842753,2,\"-----BEGIN EC PARAMETERS-----\nBggqhkjOPQMBBw==\n-----END EC PARAMETERS-----\n-----BEGIN EC PRIVATE KEY-----\nMHcCAQEEIK3K5BV1kRjtkvGPFaE+xCvJ9NoagCzxeLTUzOempGKmoAoGCCqGSM49\nAwEHoUQDQgAEpdSfGv6PlZl2ADvjslGfU5EjRLVIDxbgVDEEK8TDOhWIuncxq+YM\nd47Bk589bJQ71jFxlPN4nAhKQyy/D63/PQ==\n-----END EC PRIVATE KEY-----\n\"\r\n"

////10
//// CA Certificaste
//#define caCert "AT%CMNG=0,16842753,0,\"-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----\n\"\r\n"
//
//// Client Certificate
//#define clientCert "AT%CMNG=0,16842753,1,\"-----BEGIN CERTIFICATE-----\nMIICuDCCAaACCQCh3ScwMASc1TANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJO\nTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNVBAoM\nFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4Yjkw\nMCAXDTI0MTEwNDE0MjcyNVoYDzIwNTQxMDI4MTQyNzI1WjCBmDELMAkGA1UEBhMC\nTk8xEjAQBgNVBAgMCVRyb25kZWxhZzESMBAGA1UEBwwJVHJvbmRoZWltMSEwHwYD\nVQQKDBhOb3JkaWMgU2VtaWNvbmR1Y3RvciBBU0ExLTArBgNVBAMMJDUwNDI1MjMz\nLTM1MzUtNDM4NC04MGVjLTEyMmFmZDI4NDlhOTEPMA0GA1UELhMGMTIzNDU2MFkw\nEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEsIDxKD2aT2OmzsWSOjnevrc8GaML9evx\nRGe2DdzeH153RkM77BW6K4NI+Rx0awouWmQxHoxUH6SEXUKJyypgRTANBgkqhkiG\n9w0BAQsFAAOCAQEAqbWvwwE96jFWgvMEnHAqajDvUFRPoiFRyuS9NfS01rxpFr74\nw3F+bdrU+1TDvsHkkmNKMOFmlP5dhAjZaHgdV5y+PlArsc+lAhydDU0/Ild6hlBw\n63DUL3EOAX2fZyew4KD70WHqo4SRAKGAcPS0Wl9GG5fxMr4y1Zz575O1Mjq3uFAa\nQLknZr/4/M9QXuR7LP5kE7QwAGohctdUu8msHuoj2R9MmerSl8+PXKgCnWeQvKj6\nYSjHRPP7CdbSk6tVLAOo42PaUV0oA3IE6XsVlgCGPZgNOenyo82fBY+fcGthumZX\n/cPG/SRGZSEjjs2sIkBr1uBoVgg0AnJBFQpz+w==\n-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----\nMIIDqzCCApOgAwIBAgIJAOXo6/ALtz+gMA0GCSqGSIb3DQEBCwUAMGwxCzAJBgNV\nBAYTAk5PMQ8wDQYDVQQIDAZOb3J3YXkxEjAQBgNVBAcMCVRyb25kaGVpbTEdMBsG\nA1UECgwUTm9yZGljIFNlbWljb25kdWN0b3IxGTAXBgNVBAsMEEdlbmVyaWMtMTRh\nMThiOTAwHhcNMjMwMzE2MDMzODAwWhcNMjYwMTAzMDMzODAwWjBsMQswCQYDVQQG\nEwJOTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNV\nBAoMFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4\nYjkwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2CE46Te7DvZxfauo\nCZhNGpvJ/RNP5cfunU3qnzhpnpDwbgMT8lU2zMe14kolzNr2LQN09EYSDmBYh5je\nszKUT1FKKvMAs59UnPrdLiwWG6tWhfa5CzsNgMi+TjGcqK8K7D+Gv+b7EzDqtYFM\ng5FovJE6wYO/DIHRq7dVa21B3GB2vqiQZCXuef8kc1NCAXFm2MX5lkV6MQxyXYBo\nV8+/jNTiXSriGFJVG6MvF4lRTKC0TTV2NBFaJmRDwEuBoUSpbNoNDhhNOm+kbVBH\nlfXP81YwNOl+RVNbjGmA2lG3SEf/42jsCiaKjXp1cozF+EKGI8/H7ryMyoq0a3dG\nEFy7zwIDAQABo1AwTjAdBgNVHQ4EFgQU8QcvSXGLHmKmu6LrgIobANmjQ6IwHwYD\nVR0jBBgwFoAU8QcvSXGLHmKmu6LrgIobANmjQ6IwDAYDVR0TBAUwAwEB/zANBgkq\nhkiG9w0BAQsFAAOCAQEAAuXJuAx2BBDh44ljxqQsfLfhDNN3J8LZeoG5wbcSKQw6\nXCBp4BO/oeL8SWZ8G7WmTIxxpWyf5wBEvVGqmUnKj+skRXKVsHon63+ihomGDZTM\nb+lsPJFH0XYvmFhYhRMnDJC5FVyhsyRloyWgmRcsFoXqlkySPD8qN7/EXvHdcQwI\nB4d6mfcN9943Oywh72GdlMPxvmdBsOoRDP46Hb8NoVlEcgvNT4SWfjh6AHZiqO5r\n2NOCvvbO8S2r1NzCXBuBPtm5dY/hmbZOCiTBnK7SX6Aol24rVH7vuYOW0iLv30O2\nqke6pyCrthgdokfe2kd94L/Saos6cR8phmH5SqkZFg==\n-----END CERTIFICATE-----\n\"\r\n"
//// Private Key
//#define privateKey "AT%CMNG=0,16842753,2,\"-----BEGIN EC PARAMETERS-----\nBggqhkjOPQMBBw==\n-----END EC PARAMETERS-----\n-----BEGIN EC PRIVATE KEY-----\nMHcCAQEEIOyDpc3xchGUnWJw6wpTmIV77I2H5Q8T7c9JCAUpibE2oAoGCCqGSM49\nAwEHoUQDQgAEsIDxKD2aT2OmzsWSOjnevrc8GaML9evxRGe2DdzeH153RkM77BW6\nK4NI+Rx0awouWmQxHoxUH6SEXUKJyypgRQ==\n-----END EC PRIVATE KEY-----\n\"\r\n"


// MQTT Topic
#define NEW_BAND_TOPIC "AT#XMQTTPUB=\"/DT/eHG4/Status/Band\"\r\n"
#define	OLD_BAND_TOPIC "AT#XMQTTPUB=\"/efwb/post/sync\"\r\n"

#define NEW_BANDALERT_TOPIC "AT#XMQTTPUB=\"/DT/eHG4/Status/BandAlert\"\r\n"
#define OLD_BANDALERT_TOPIC "AT#XMQTTPUB=\"/efwb/post/async\"\r\n"

#define NEW_FALLDETECTION_TOPIC "AT#XMQTTPUB=\"/DT/eHG4/Status/FallDetection\"\r\n"
#define OLD_FALLDETECTION_TOPIC "AT#XMQTTPUB=\"/efwb/post/async\"\r\n"

#define IMU_TOPIC 			"AT#XMQTTPUB=\"/DT/eHG4/Status/IMU\"\r\n"
#define GPS_LOCATION_TOPIC	"AT#XMQTTPUB=\"/DT/eHG4/GPS/Location\"\r\n"

#define UUID_TOPIC	"AT#XMQTTPUB=\"/DT/eHG4/UUID\"\r\n"
#define FALLDETECTION_CHECK_TOPIC	"AT#XMQTTPUB=\"/DT/eHG4/FallDetection_Check\"\r\n"
#define BATTDATA_CHECK_TOPIC		"AT#XMQTTPUB=\"/DT/eHG4/BattData_Check\"\r\n"

#define SUB_STATUS_BANDSET 	"AT#XMQTTSUB=\"/DT/test_eHG4/Status/BandSet\",0\r\n"
#define SUB_SERVER_ALERT	"AT#XMQTTSUB=\"/DT/eHG4/Status/ServerAlert\",0\r\n"

typedef enum {
    WPM_INIT_CHECK,
    WPM_INIT_COMPLETE
} WpmState;

typedef enum {
    SYSTEM_MODE_CHECK,
    CFUN_CHECK,
    CONNECTION_CHECK,
    FINAL_COMMANDS,
    CHECK_COMPLETE
} CheckState;

typedef enum {
    MQTT_INIT,
    MQTT_CONFIG,
    MQTT_CONNECT,
    MQTT_SUBSCRIBE_STATUS,
    MQTT_SUBSCRIBE_ALERT,
    MQTT_COMPLETE
} MqttState;

typedef enum {
    GPS_INIT,
    GPS_SYSTEM_MODE,
    GPS_CFUN,
    GPS_ON,
    GPS_COMPLETE
} GpsState;

// Constants
#define MAX_CMD_LEN 100
#define MAX_VALUE_LEN 100
#define MAX_PARAMS_LEN 100
#define MAX_RESPONSE_LEN 256

#define ICCID_LEN 21

#define CAT_M1_UART_BUF_SIZE 512

#define mqtt_operation_cycle 60*10 // CatM1 MQTT => 10min interval
#define GNSS_INTERVAL_SEC 60*(72*60) // GNSS => (72*60)min interval

typedef struct {
	uint8_t txflag;
	uint8_t InitialLoad;
	uint8_t Checked;
    uint8_t parseCount;
    uint8_t parseResult;
    uint8_t bootCount;
    uint8_t errorCount;
    uint8_t retryCount;
    uint8_t cfunStatus;
    uint8_t systemModeStatus;
    uint8_t connectionStatus;
    uint8_t mqttSetStatus;
    uint8_t mqttConnectionStatus;
    uint8_t mqttSubscribeStatus;
    uint8_t gpsOn;
    uint8_t gpsOff;
    uint8_t mqttChecking;
    uint8_t gpsChecking;
} cat_m1_Status_t;

typedef struct {
  uint8_t head;
  uint8_t tail;
  uint8_t buffer[CAT_M1_UART_BUF_SIZE];
  uint8_t rxd;
  uint8_t temp;
  bool done;
} uart_cat_m1_t;

typedef struct {
  uint8_t buffer[MAX_RESPONSE_LEN];
  uint8_t cops[MAX_VALUE_LEN];
  uint8_t cgdcont[MAX_VALUE_LEN];
  uint8_t iccid[ICCID_LEN];
  uint8_t networkinfo[180];
  uint8_t cesq[100];
  uint8_t gps[100];
  uint8_t uuid[100];
  int altitude;
  uint8_t time[25];
  uint8_t cnum[100];
  int  rssi;
} cat_m1_at_cmd_rst_t;

typedef struct {
  uint32_t bid;
  uint16_t pid;
  int  rssi;
  uint8_t start_byte;
  uint16_t hr;
  uint16_t spo2;
  uint8_t motionFlag;
  uint8_t scdState;
  uint8_t activity;
  uint32_t walk_steps;
  uint32_t run_steps;
  uint32_t temperature;
  int pres;
  uint8_t battery_level;
} cat_m1_Status_Band_t;

typedef struct {
  uint32_t bid;
//  uint8_t hr_alert;
//  uint8_t spo2_alert;
  uint8_t type;
  uint8_t value;
} cat_m1_Status_BandAlert_t;

typedef struct {
  uint32_t bid;
  uint8_t type;
  uint8_t fall_detect;
} cat_m1_Status_FallDetection_t;

typedef struct {
  uint32_t bid;
  int data;
  int accScal_data;
} cat_m1_Status_Fall_Difference_Value_t;

typedef struct {
  uint32_t bid;
  int level;
  int voltage;
} cat_m1_Status_BATTData_Value_t;

typedef struct {
  uint32_t bid;
} cat_m1_Status_GPS_Location_t;

typedef struct {
  uint32_t bid;
} cat_m1_Status_uuid_t;

typedef struct {
  uint32_t bid;
  int16_t acc_x;
  int16_t acc_y;
  int16_t acc_z;

  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;

  int16_t mag_x;
  int16_t mag_y;
  int16_t mag_z;
} cat_m1_Status_IMU_t;

typedef struct {
  uint32_t bid;
  uint8_t hr_min;
  uint8_t hr_max;
  uint8_t spo2_min;
  uint8_t spo2_max;
  uint8_t height;
  uint8_t weight;
} cat_m1_Status_BandSet_t;

typedef struct {
  uint32_t bid;
  uint8_t alert;
} cat_m1_Status_ServerAlert_t;

typedef struct{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}catM1Time;

extern uart_cat_m1_t uart_cat_m1_rx;

void clear_uart_buf(uart_cat_m1_t* u);
void push(uart_cat_m1_t* u, uint8_t data);
uint8_t pop(uart_cat_m1_t* u);
uint8_t isEmpty(uart_cat_m1_t* u);

// External UART handle (replace huart1 with the appropriate UART handle if needed)
extern UART_HandleTypeDef huart1;

// UART Communication related functions
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
bool send_at_command(const char *cmd);
bool receive_at_command_ret(void);
bool receive_response(void);
bool cat_m1_parse_process(uint8_t *msg);
void cat_m1_parse_result(const char *command, const char *value);
void handle_cops_command(const char *value);
void handle_cfun_command(const char *value);
void handle_system_mode_command(const char *value);
void handle_mqtt_cfg_command(const char *value);
void handle_cgdcont_command(const char *value);
void handle_iccid_command(const char *value);
void handle_monitor_command(const char *value);
void handle_cesq_command(const char *value);
void handle_gps_command(const char *value);
void handle_cell_location_command(const char *value);
void handle_mqtt_event_command(const char *value);
void handle_cclk_command(const char *value);
void handle_xuuid_command(const char *value);
void handle_cnum_command(const char *value);

// nRF9160 Modem Interaction
void uart_init();
void nrf9160_clear_buf();
void nrf9160_init();
void nrf9160_ready();
void nrf9160_check();

void nrf9160_mqtt_setting();
void nrf9160_mqtt_test();
void test_send_json_publish();
void send_Status_Band(cat_m1_Status_Band_t *status);
void send_Status_BandAlert(cat_m1_Status_BandAlert_t* alertData);
void send_Status_FallDetection(cat_m1_Status_FallDetection_t* fallData);
void send_GPS_Location(cat_m1_Status_GPS_Location_t* location);
void send_Status_IMU(cat_m1_Status_IMU_t* imu_data);
void send_UUID(cat_m1_Status_uuid_t* uuid);
void send_Fall_Difference_Value(cat_m1_Status_Fall_Difference_Value_t* Fall_Difference);
void send_BATTData_Value(cat_m1_Status_BATTData_Value_t* battData);

void nrf9160_Get_gps();
void nrf9160_Stop_gps();
void nrf9160_Get_gps_State();
void nrf9160_Get_rssi();
void nrf9160_Get_time();
void catM1Reset();
void catM1nRFCloud_Init();
void catM1PWRGPIOInit();

void nrf9160_Get_cell_location();

catM1Time getCatM1Time(void);

time_t convertToTimeT(catM1Time dt);
bool isDifferenceWithinNMinute(catM1Time dt1, catM1Time dt2, uint16_t thresholdTime);

#endif /* CATM1_NRF9160_H_ */
