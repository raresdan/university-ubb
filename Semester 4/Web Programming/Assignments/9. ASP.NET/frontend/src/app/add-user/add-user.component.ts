import {Component, OnInit} from '@angular/core';
import {UserService} from '../user.service';
import {Router, RouterLink} from '@angular/router';
import { FormBuilder, FormGroup, ReactiveFormsModule, Validators } from '@angular/forms';

@Component({
  selector: 'app-add-user',
  standalone: true,
  imports:[
    ReactiveFormsModule,
    RouterLink
  ],
  templateUrl: './add-user.component.html',
  styleUrls: ['./add-user.component.css']
})
export class AddUserComponent implements OnInit {
  addUserForm: FormGroup = new FormGroup({});

  constructor(private formBuilder: FormBuilder, private service: UserService, private router: Router) {}

  ngOnInit() {
    this.addUserForm = this.formBuilder.group({
      name: ['', Validators.required],
      username: ['', Validators.required],
      password: ['', Validators.required],
      age: [null],
      role: [''],
      email: ['', Validators.required],
      webpage: ['']
    });
  }

  onSubmit() {
    if (this.addUserForm.invalid) {
      return;
    }
    this.service.addUser(this.addUserForm.value).subscribe({
      next: response => {
          this.router.navigate(['/users']);
          console.log('User added successfully.', response);
      },
      error: error => {
        console.error('Error adding user:', error);
      }
    });
  }
}
