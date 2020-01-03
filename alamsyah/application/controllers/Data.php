<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Data extends CI_Controller {
	function __construct(){
		parent::__construct();
		$this->load->model('Data_model');
	}
	// What we do ? : insert into database data from defice or sensor
	// If (data > 200) then send notif to firebase :

	public function index(){
		echo "Nothing !";
	}

	function insert($data){
		$exe = $this->Data_model->insert($data);
		if($exe){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
}
