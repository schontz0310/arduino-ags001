String _payload = "";
String _temp = "";
  
String jsonAssignCompanyMount(){
  _temp = String(getTimestamp());
  _temp.remove(10, 9);

  _payload = "{";
  _payload += "\"d\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(0, 11);

  _payload += "\"h\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _payload += "\"e\":";
  _payload += "\"";
  _payload += String(getUID());
  _payload += "\"";
  _payload += ",";

  _payload += "\"c\":";
  _payload += "\"";
  _payload += String("080");
  _payload += "\"";
  _payload += ",";

  _payload += "\"cy\":";
  _payload += "\"";
  _payload += String(companyNumber);
  _payload += "\"";

  _payload += "}";

  return _payload;  
}

String jsonHorimeterParameterMount(bool toogle){
  _temp = String(getTimestamp());
  _temp.remove(10, 9);

  _payload = "{";
  _payload += "\"d\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(0, 11);

  _payload += "\"h\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _payload += "\"e\":";
  _payload += "\"";
  _payload += String(getUID());
  _payload += "\"";
  _payload += ",";

  _payload += "\"c\":";
  _payload += "\"";
  _payload += String("081");
  _payload += "\"";
  _payload += ",";

  _payload += "\"hp\":";
  _payload += "\"";
  _payload += String(toogle);
  _payload += "\"";
  _payload += ",";
  
  _payload += "\"cy\":";
  _payload += "\"";
  _payload += String(COMPANY);
  _payload += "\"";

  _payload += "}";

  return _payload;  
}


String jsonPermissionMount(){
  _payload = "";
  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(10, 9);
  //_temp.remove(2, 1);
  //_temp.remove(4, 1);

  _payload = "{";
  _payload += "\"d\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(0, 11);

  _payload += "\"h\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _payload += "\"e\":";
  _payload += "\"";
  _payload += String(getUID());
  _payload += "\"";
  _payload += ",";

  _payload += "\"c\":";
  _payload += "\"";
  _payload += String("003");
  _payload += "\"";
  _payload += ",";

  _payload += "\"pt\":";
  _payload += "\"";
  _payload += String(_UUIDPermission);
  _payload += "\"";

  _payload += "}";

  return _payload;

}


String jsonVehicleMount(){
  _payload = "";
  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(10, 9);
  
  _payload = "{";
  _payload += "\"d\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(0, 11);

  _payload += "\"h\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _payload += "\"e\":";
  _payload += "\"";
  _payload += String(getUID());
  _payload += "\"";
  _payload += ",";

  _payload += "\"c\":";
  _payload += "\"";
  _payload += String("002");
  _payload += "\"";
  _payload += ",";

  _payload += "\"vt\":";
  _payload += "\"";
  _payload += String(tagUuid);
  _payload += "\"";
  _payload += ",";

  _payload += "\"vn\":";
  _payload += "\"";
  _payload += String(_vehicleName);
  _payload += "\"";
  _payload += ",";

  _payload += "\"vf\":";
  _payload += "\"";
  _payload += String(_vehicleFuel);
  _payload += "\"";

  _payload += "}";

  return _payload;
}


String jsonOperatorMount(){
  _payload = "";
  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(10, 9);
  //_temp.remove(2, 1);
  //_temp.remove(4, 1);

  _payload = "{";
  _payload += "\"d\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(0, 11);

  _payload += "\"h\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _payload += "\"e\":";
  _payload += "\"";
  _payload += String(getUID());
  _payload += "\"";
  _payload += ",";

  _payload += "\"c\":";
  _payload += "\"";
  _payload += String("001");
  _payload += "\"";
  _payload += ",";

  _payload += "\"ot\":";
  _payload += "\"";
  _payload += String(tagUuid);
  _payload += "\"";
  _payload += ",";

  _payload += "\"on\":";
  _payload += "\"";
  _payload += String(_operatorName);
  _payload += "\"";
  _payload += ",";

  _payload += "\"ol\":";
  _payload += "\"";
  _payload += String(_operatorLevel);
  _payload += "\"";

  _payload += "}";

  return _payload;
}


String jsonFuelChargeMount(){
  _payload = "";
  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(10, 9);

  _payload = "{";
  _payload += "\"d\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _temp = "";
  _temp = String(getTimestamp());
  _temp.remove(0, 11);

  _payload += "\"h\":";
  _payload += "\"";
  _payload += String(_temp);
  _payload += "\"";
  _payload += ",";

  _payload += "\"e\":";
  _payload += "\"";
  _payload += String(getUID());
  _payload += "\"";
  _payload += ",";

  _payload += "\"c\":";
  _payload += "\"";
  _payload += String("099");
  _payload += "\"";
  _payload += ",";

  _payload += "\"ot\":";
  _payload += "\"";
  _payload += String(_operatorUuid);
  _payload += "\"";
  _payload += ",";

  _payload += "\"on\":";
  _payload += "\"";
  _payload += String(_operatorName);
  _payload += "\"";
  _payload += ",";

  _payload += "\"ol\":";
  _payload += "\"";
  _payload += String(_operatorLevel);
  _payload += "\"";
  _payload += ",";

  _payload += "\"vt\":";
  _payload += "\"";
  _payload += String(_vehicleUuid);
  _payload += "\"";
  _payload += ",";

  _payload += "\"vn\":";
  _payload += "\"";
  _payload += String(_vehicleName);
  _payload += "\"";
  _payload += ",";

  _payload += "\"vf\":";
  _payload += "\"";
  _payload += String(_vehicleFuel);
  _payload += "\"";
  _payload += ",";

  _payload += "\"vo\":";
  _payload += "\"";
  _payload += String(ODOMETER_VALUE);
  _payload += "\"";
  _payload += ",";

  _payload += "\"fq\":";
  _payload += "\"";
  _payload += String(fuelQuantity);
  _payload += "\"";
  _payload += ",";

  _payload += "\"cy\":";
  _payload += "\"";
  _payload += String(COMPANY);
  _payload += "\"";

  _payload += "}";

  return _payload;
}
