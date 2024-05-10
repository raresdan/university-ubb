import { Component, OnInit } from '@angular/core';
import {UserService} from '../user.service';
import {ActivatedRoute, Router, RouterLink} from '@angular/router';
import { FormBuilder, FormGroup, ReactiveFormsModule, Validators } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-update-user',
  standalone: true,
  imports:[
    CommonModule,
    ReactiveFormsModule,
    RouterLink
  ],
  templateUrl: './update-user.component.html',
  styleUrls: ['./update-user.component.css']
})
export class UpdateUserComponent implements OnInit {
  updateUserForm: FormGroup = new FormGroup({});
  constructor(private formBuilder: FormBuilder, private service: UserService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.initializeForm();
    const id = this.route.snapshot.queryParams['id'];
    this.service.getUserData(id).subscribe((user) => {
    this.updateUserForm.patchValue({
      name: user.name,
      username: user.username,
      password: user.password,
      age: user.age,
      role: user.role,
      email: user.email,
      webpage: user.webpage
    });
  });
  }

  initializeForm() {
    this.updateUserForm = this.formBuilder.group({
      id: [''],
      name: ['', Validators.required],
      username: ['', Validators.required],
      password: ['', Validators.required],
      age: [null],
      role: [''],
      email: ['', Validators.required],
      webpage: ['']
    });
  }

  updateUser(name: string, username: string, password: string, age: string, role: string, email: string, webpage: string): void {
    const id = this.route.snapshot.queryParams['id'];
    const userData = {
      name: name,
      username: username,
      password: password,
      age: age,
      role: role,
      email: email,
      webpage: webpage
    };
    this.service.updateUser(id.toString(), userData).subscribe({
      next: () => {
        this.router.navigate(['/']).then(_ => {
        });
      },
      error: (error) => {
        console.error('There was an error updating the user', error);
      }
    });
  }

  onSubmit(): void {
    if (this.updateUserForm.invalid) {
      return;
    }
    this.updateUser(this.updateUserForm.value.name, this.updateUserForm.value.username, this.updateUserForm.value.password, this.updateUserForm.value.age, this.updateUserForm.value.role, this.updateUserForm.value.email, this.updateUserForm.value.webpage);
  }

}
