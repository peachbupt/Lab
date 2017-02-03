# demo-restful API

##Overview

###Version information
*Version* : 1.0.0

##Paths

###POST /website
#### Description

Create a new `demo` object.

#### Parameters
|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Body**|**website**  <br>*required*|New Item to add to Website |[Website](#website)||

#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|Successful response|[Website](#website)|

### GET /website

#### Parameters

|Type|Name|Description|Schema|Default|
|---|---|---|---|---|
|**Query**|**number**  <br>*optional*|Number of website to retrieve|integer(int32)||


#### Responses

|HTTP Code|Description|Schema|
|---|---|---|
|**200**|Successful response|<[Website](#website)> array|

<a name="definitions"></a>
## Definitions

<a name="pokemon"></a>
### Website

|Name|Description|Schema|
|---|---|---|
|**name**  <br>*required*|Name of the Website |string|
|**number**  <br>*required*|Number of the Website|integer(int32)|