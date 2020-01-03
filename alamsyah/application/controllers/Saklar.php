<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Saklar extends CI_Controller {
	function __construct(){
		parent::__construct();
		$this->load->model('Saklar_model');
	}
	// id_saklar
	// nama_saklar
	// status
	// update data saklar 1 : 0  1= nyala 0 = mati
	public function index(){
		echo "Nothing !";
	}
	// ALAT
	function status($id){
		$datas = $this->Saklar_model->get_by_id($id);
		foreach ($datas as $data) {
			echo $data->status;
		}
	}


}
